// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once
#include "mx/api/DocumentManager.h"
#include <string>

namespace mx
{
    namespace core
    {
        class Document;
    }

    namespace api
    {
        // MxCorePtr, implemented in DocumentManager.cpp, is a wrapper for a mx::core::DocumentPtr. This gives a
        // 'power user' a way to specify most of their MusicXML document using the mx::api data structure, but then to
        // retrieve the mx::core::DocumentPtr from the mx::api::DocumentManager for further tweaking ot the DOM. This
        // class should be ignored by most developers unless they find they need to do something with MusicXML that
        // is not supported by mx::api.
        class MxCorePtr
        {
        public:
            ~MxCorePtr();
            MxCorePtr( const MxCorePtr& other );
            MxCorePtr( MxCorePtr&& inOther ) noexcept;
            MxCorePtr& operator=( const MxCorePtr& inOther );
            MxCorePtr& operator=( MxCorePtr&& inOther ) noexcept;

        private:
            friend class DocumentManager;
            friend class mx::core::Document;

        private:
            class Impl;
            std::unique_ptr<Impl> myImpl;
            MxCorePtr( std::unique_ptr<Impl>&& inImpl );
        };
    }
}
