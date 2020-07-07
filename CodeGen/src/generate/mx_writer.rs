use crate::generate::mx_enum_writer::MxEnumWriter;
use std::io::Write;

pub struct MxWriter {
    pub enum_writer: MxEnumWriter,
}

impl MxWriter {
    pub fn new(enum_writer: MxEnumWriter) -> Self {
        Self { enum_writer }
    }

    pub fn write_enum_declarations<W: Write>(&self, w: &mut W) -> std::io::Result<()> {
        self.enum_writer.write_declarations(w)
    }

    pub fn write_enum_definitions<W: Write>(&self, w: &mut W) -> std::io::Result<()> {
        self.enum_writer.write_definitions(w)
    }
}
