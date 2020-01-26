// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mxtest/control/CompileControl.h"
#ifdef MX_COMPILE_API_TESTS

    #include "cpul/cpulTestHarness.h"
    #include "mx/api/DocumentManager.h"
    #include "mx/api/ScoreData.h"
    #include "mx/core/Document.h"
    #include "mx/core/Document.h"
    #include "mx/core/elements/Direction.h"
    #include "mx/core/elements/DirectionType.h"
    #include "mx/core/elements/FullNoteGroup.h"
    #include "mx/core/elements/FullNoteTypeChoice.h"
    #include "mx/core/elements/MusicDataChoice.h"
    #include "mx/core/elements/MusicDataGroup.h"
    #include "mx/core/elements/MusicDataGroup.h"
    #include "mx/core/elements/NormalNoteGroup.h"
    #include "mx/core/elements/Notations.h"
    #include "mx/core/elements/NotationsChoice.h"
    #include "mx/core/elements/Note.h"
    #include "mx/core/elements/NoteChoice.h"
    #include "mx/core/elements/Offset.h"
    #include "mx/core/elements/PartwiseMeasure.h"
    #include "mx/core/elements/PartwiseMeasure.h"
    #include "mx/core/elements/PartwisePart.h"
    #include "mx/core/elements/PartwisePart.h"
    #include "mx/core/elements/Pedal.h"
    #include "mx/core/elements/Pitch.h"
    #include "mx/core/elements/ScorePartwise.h"
    #include "mx/core/elements/ScorePartwise.h"
    #include "mx/core/elements/Tied.h"
    #include "mxtest/api/RoundTrip.h"
    #include "mxtest/api/TestHelpers.h"

using namespace std;
using namespace mx::api;
using namespace mxtest;

TEST( DbMinorIsSupported, KeyData )
{
    mx::api::ScoreData score;
    score.workTitle = "Db Minor";
    mx::api::PartData part;
    part.displayName = "Flute";
    part.instrumentData.uniqueId = "FLUTE1";
    part.instrumentData.soloOrEnsemble = SoloOrEnsemble::solo;
    part.instrumentData.soundID = SoundID::windFlutesFlute;
    part.measures.emplace_back();
    auto& measure = part.measures.back();
    mx::api::KeyData dbMinor;
    dbMinor.fifths = -8;
    dbMinor.mode = KeyMode::minor;
    measure.keys.push_back( dbMinor );
    score.parts.push_back( std::move(part));
    auto& docMgr = mx::api::DocumentManager::getInstance();
    const auto id = docMgr.createFromScore( score );
    std::cout << std::endl;
    docMgr.writeToStream(id, std::cout);
    std::cout << std::endl;
}

#endif