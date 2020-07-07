pub mod builtin;
pub mod create;
pub mod creator;
pub mod enumeration;
pub mod symbol;

use crate::generate::string_stuff::tokenize;
use crate::model::create::{Create, CreateError, CreateResult};
use crate::model::enumeration::Enumeration;
use crate::model::symbol::Symbol;
use crate::xsd::restriction::Facet;
use crate::xsd::simple_type::{Payload, SimpleType};
use crate::xsd::{simple_type, Entry, Xsd};
use std::borrow::Borrow;
use std::ops::Deref;

#[derive(Debug, Clone, Eq, PartialEq, Ord, PartialOrd)]
pub enum Model {
    Enumeration(Enumeration),
}

#[derive(Debug, Clone, Copy, Eq, PartialEq, Ord, PartialOrd)]
pub struct DefaultCreate {}

impl Default for DefaultCreate {
    fn default() -> Self {
        Self {}
    }
}

impl Create for DefaultCreate {
    fn name(&self) -> &'static str {
        "default"
    }

    fn create(&self, entry: &Entry, xsd: &Xsd) -> CreateResult {
        match entry {
            Entry::Annotation(_) => Ok(None),     // TODO - implement Annotation
            Entry::AttributeGroup(_) => Ok(None), // TODO - implement AttributeGroup
            Entry::ComplexType(_) => Ok(None),    // TODO - implement ComplexType
            Entry::Element(_) => Ok(None),        // TODO - implement Element
            Entry::Group(_) => Ok(None),          // TODO - implement Group
            Entry::Import(_) => Ok(None),         // TODO - implement Import
            Entry::SimpleType(st) => {
                if is_enumeration(st) {
                    model_enumeration(st, xsd)
                } else {
                    unimplemented!();
                }
            }
        }
    }
}

fn is_enumeration(st: &SimpleType) -> bool {
    match &st.payload {
        Payload::Restriction(r) => {
            for facet in &r.facets {
                match facet {
                    Facet::Enumeration(_) => continue,
                    _ => return false,
                }
            }
            return true;
        }
        _ => false,
    }
}

fn model_enumeration(st: &SimpleType, xsd: &Xsd) -> CreateResult {
    let restriction = if let simple_type::Payload::Restriction(r) = &st.payload {
        r
    } else {
        return Err(CreateError::new("expected restriction"));
    };
    let mut members = Vec::new();
    for facet in &restriction.facets {
        let s = if let Facet::Enumeration(s) = facet {
            s
        } else {
            return Err(CreateError::new("expected enumeration"));
        };
        members.push(Symbol::new(s.as_str()));
    }
    let enm = Enumeration {
        name: Symbol::new(st.id.name()),
        members,
        documentation: st.documentation(),
        other_field: None,
    };
    Ok(Some(vec![Model::Enumeration(enm)]))
}
