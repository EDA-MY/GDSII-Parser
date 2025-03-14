#ifndef GDSII_COPMMON_HPP
#define GDSII_COPMMON_HPP

#include <iostream>
#include <unordered_map>

enum class GDSIIRecordType : uint16_t {
    // File header records
    GDSIIHeaderRecord   = 0x0002,
    GDSIIBgnLib         = 0x0102,
    GDSIILibName        = 0x0206,
    GDSIIRefLibs        = 0x1F06,
    GDSIIFonts          = 0x2006,
    GDSIIAttrTable      = 0x2306,
    GDSIIGenerations    = 0x2202,
    GDSIIFormat         = 0x3602,
    GDSIIMask           = 0x3706,
    GDSIIEndMasks       = 0x3800,
    GDSIIUnits          = 0x0305,

    // File tail records
    GDSIIEndLib         = 0x0400,

    // Structure header records
    GDSIIBgnStr         = 0x0502,
    GDSIIStrName        = 0x0606,

    // Structure tail records
    GDSIIEndStr         = 0x0700,

    // Element header records
    GDSIICounday        = 0x0800,
    GDSIIPath           = 0x0900,
    GDSIISref           = 0x0A00,
    GDSIIAref           = 0x0B00,
    GDSIIText           = 0x0C00,
    GDSIINode           = 0x1500,
    GDSIIBox            = 0x2D00,

    // Element content records
    GDSIIELFlags        = 0x2601,
    GDSIIPlex           = 0x2F03,
    GDSIILayer          = 0x0D02,
    GDSIIDataType       = 0x0E02,
    GDSIIXY             = 0x1003,
    GDSIIPathType       = 0x2102,
    GDSIIWidth          = 0x0F03,
    GDSIIEndEl          = 0x1100,
    GDSIISName          = 0x1206,
    GDSIISTrans         = 0x1A01,
    GDSIIMag            = 0x1B05,
    GDSIIAngle          = 0x1C05,
    GDSIIColRow         = 0x1302,
    GDSIITextType       = 0x1602,
    GDSIIPresentation   = 0x1701,
    GDSIIASCIIString    = 0x1906,
    GDSIINodeType       = 0x2A02,
    GDSIIBoxType        = 0x2E02,

    // Maximum record type
    GDSIIEndRecordType  = 0x0000
};

// Unordered map for faster lookups
static std::unordered_map<uint16_t, std::string> recordEnumToStringMap = {
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIHeaderRecord ) , "Header Record"         },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIBgnLib       ) , "Begin Library"         },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIILibName      ) , "Library Name"          },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIRefLibs      ) , "Referenced Libraries"  },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIFonts        ) , "Fonts"                 },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIAttrTable    ) , "Attribute Table"       },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIGenerations  ) , "Generations"           },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIFormat       ) , "Format"                },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIMask         ) , "Mask"                  },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIEndMasks     ) , "End Masks"             },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIUnits        ) , "Units"                 },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIEndLib       ) , "End Library"           },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIBgnStr       ) , "Begin Structure"       },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIStrName      ) , "Structure Name"        },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIEndStr       ) , "End Structure"         },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIICounday      ) , "Boundary"              },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIPath         ) , "Path"                  },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIISref         ) , "SRef"                  },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIAref         ) , "ARef"                  },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIText         ) , "Text"                  },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIINode         ) , "Node"                  },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIBox          ) , "Box"                   },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIELFlags      ) , "Element Flags"         },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIPlex         ) , "PLEX"                  },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIILayer        ) , "Layer"                 },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIDataType     ) , "Data Type"             },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIXY           ) , "XY"                    },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIPathType     ) , "Path Type"             },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIWidth        ) , "Width"                 },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIEndEl        ) , "End Element"           },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIISName        ) , "SName"                 },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIISTrans       ) , "Transformation"        },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIMag          ) , "MAG"                   },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIAngle        ) , "Angle"                 },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIColRow       ) , "ColRow"                },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIITextType     ) , "Text Type"             },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIPresentation ) , "Presentation"          },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIASCIIString  ) , "ASCII String"          },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIINodeType     ) , "Node Type"             },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIBoxType      ) , "Box Type"              },
    { static_cast<uint16_t>(GDSIIRecordType::GDSIIEndRecordType) , "End File Header"       }
};

#endif