project(piadata CXX)


################################################################################
# Source groups
################################################################################
set(Headers
    "../include/Assumptions.h"
    "../include/AssumptionsFile.h"
    "../include/AssumptionsNonFile.h"
    "../include/AssumptionType.h"
    "../include/avgwg.h"
    "../include/awbidat.h"
    "../include/AwbiDataFile.h"
    "../include/AwbiDataNonFile.h"
    "../include/awinc.h"
    "../include/AwincDoc.h"
    "../include/AwincFile.h"
    "../include/AwincNonFile.h"
    "../include/BaseChangeType.h"
    "../include/baseyear.h"
    "../include/BaseYearFile.h"
    "../include/BaseYearNonFile.h"
    "../include/bendmfb.h"
    "../include/bendpia.h"
    "../include/BendPoints.h"
    "../include/BenefitAmount.h"
    "../include/BenefitAmountArray.h"
    "../include/bic.h"
    "../include/biproj.h"
    "../include/BiprojFile.h"
    "../include/BiprojNonFile.h"
    "../include/BitAnnual.h"
    "../include/bpmfbout.h"
    "../include/bppiaout.h"
    "../include/cachup.h"
    "../include/cachupf.h"
    "../include/CatchupFile.h"
    "../include/CatchupNonFile.h"
    "../include/ChildCareCalc.h"
    "../include/ChildCareCalcLC.h"
    "../include/comppd.h"
    "../include/config.h"
    "../include/ConfigFile.h"
    "../include/ConfigNonFile.h"
    "../include/DebugCase.h"
    "../include/DibGuar.h"
    "../include/DibGuarLC.h"
    "../include/dinscode.h"
    "../include/DisabPeriod.h"
    "../include/DisInsCodeArray.h"
    "../include/EarnProject.h"
    "../include/FieldOfficeInfoFile.h"
    "../include/FieldOfficeInfoNonFile.h"
    "../include/foinfo.h"
    "../include/FrozMin.h"
    "../include/frzyrs.h"
    "../include/inscode.h"
    "../include/InsCodeArray.h"
    "../include/LawChange.h"
    "../include/LawChangeAGE65COMP.h"
    "../include/LawChangeALLEARN.h"
    "../include/LawChangeArray.h"
    "../include/LawChangeBPFRACWAGE.h"
    "../include/LawChangeBPMINCONST.h"
    "../include/LawChangeBPSPECRATE.h"
    "../include/LawChangeCHILDCARECREDIT.h"
    "../include/LawChangeCHILDCAREDROPOUT.h"
    "../include/LawChangeCOLACHANGE.h"
    "../include/LawChangeDECLINEPERC.h"
    "../include/LawChangeDROPOUTCHG.h"
    "../include/LawChangeMARRLENGTH.h"
    "../include/LawChangeNEWFORMULA.h"
    "../include/LawChangeNEWSPECMIN.h"
    "../include/LawChangeNRACHANGE.h"
    "../include/LawChangeOut.h"
    "../include/LawChangePSAACCT.h"
    "../include/LawChangeRead.h"
    "../include/LawChangeTAXBENCHG.h"
    "../include/LawChangeTAXRATECHG.h"
    "../include/LawChangeWAGEBASECHG.h"
    "../include/LawChangeWIDFACTOR.h"
    "../include/LawChangeWIFEFACTOR.h"
    "../include/LawChangeWrite.h"
    "../include/MilServDatesVec.h"
    "../include/msdates.h"
    "../include/oactcnst.h"
    "../include/OldPia.h"
    "../include/OldStart.h"
    "../include/OldStartLC.h"
    "../include/pebs.h"
    "../include/percmfb.h"
    "../include/percpia.h"
    "../include/PercPiaOut.h"
    "../include/piacal.h"
    "../include/PiaCalAny.h"
    "../include/PiaCalLC.h"
    "../include/PiaCalPL.h"
    "../include/piadata.h"
    "../include/PiadataArray.h"
    "../include/PiaMethod.h"
    "../include/PiaParamsLCTR.h"
    "../include/PiaParamsTR.h"
    "../include/piaparms.h"
    "../include/piaparmsAny.h"
    "../include/piaparmsLC.h"
    "../include/piaparmsPL.h"
    "../include/piaread.h"
    "../include/piareadAny.h"
    "../include/PiaTable.h"
    "../include/PiaTableLC.h"
    "../include/piawrite.h"
    "../include/piawriteAny.h"
    "../include/pibtable.h"
    "../include/Pifc.h"
    "../include/PortionAime.h"
    "../include/Psa.h"
    "../include/qc.h"
    "../include/qcamt.h"
    "../include/QcArray.h"
    "../include/QcPacked.h"
    "../include/railroad.h"
    "../include/ReindWid.h"
    "../include/ReindWidLC.h"
    "../include/Resource.h"
    "../include/RetireTest.h"
    "../include/rtgenrl.h"
    "../include/ScaledEarnFactors.h"
    "../include/Secondary.h"
    "../include/SecondaryArray.h"
    "../include/Sga.h"
    "../include/SgaDerived.h"
    "../include/SgaGeneral.h"
    "../include/SpecMin.h"
    "../include/SpecMinLC.h"
    "../include/ssn.h"
    "../include/TaxBenefits.h"
    "../include/TaxBenefitsLC.h"
    "../include/TaxData.h"
    "../include/TaxRates.h"
    "../include/TaxRatesLC.h"
    "../include/TaxRatesPL.h"
    "../include/TransGuar.h"
    "../include/TransGuarLC.h"
    "../include/UserAssumptions.h"
    "../include/WageBase.h"
    "../include/WageInd.h"
    "../include/WageIndGeneral.h"
    "../include/WageIndLC.h"
    "../include/WageIndNonFreeze.h"
    "../include/wbgenrl.h"
    "../include/wbgenrlLC.h"
    "../include/WorkerDataArray.h"
    "../include/WorkerDataGeneral.h"
    "../include/wrkrdata.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "Assumptions.cpp"
    "AssumptionsFile.cpp"
    "AssumptionsNonFile.cpp"
    "AssumptionType.cpp"
    "avgwg.cpp"
    "awbidat.cpp"
    "awbidtfl.cpp"
    "awbidtnf.cpp"
    "awinc.cpp"
    "AwincDoc.cpp"
    "awincfl.cpp"
    "awincnf.cpp"
    "BaseChangeType.cpp"
    "baseyear.cpp"
    "baseyrfl.cpp"
    "baseyrnf.cpp"
    "bendmfb.cpp"
    "bendpia.cpp"
    "BendPoints.cpp"
    "BenefitAmount.cpp"
    "BenefitAmountArray.cpp"
    "Bic.cpp"
    "biproj.cpp"
    "biprojfl.cpp"
    "biprojnf.cpp"
    "bpmfbout.cpp"
    "bppiaout.cpp"
    "cachpdoc.cpp"
    "cachup.cpp"
    "cachupfl.cpp"
    "cachupnf.cpp"
    "ChildCareCalc.cpp"
    "ChildCareCalcLC.cpp"
    "CompPeriod.cpp"
    "config.cpp"
    "configFile.cpp"
    "configNonFile.cpp"
    "DebugCase.cpp"
    "DibGuar.cpp"
    "DibGuarLC.cpp"
    "dinscode.cpp"
    "DisabPeriod.cpp"
    "DisInsCodeArray.cpp"
    "EarnProject.cpp"
    "foinfo.cpp"
    "foinfofl.cpp"
    "foinfonf.cpp"
    "FrozMin.cpp"
    "frzyrs.cpp"
    "inscode.cpp"
    "InsCodeArray.cpp"
    "LawChange.cpp"
    "LawChangeAGE65COMP.cpp"
    "LawChangeALLEARN.cpp"
    "LawChangeArray.cpp"
    "LawChangeBPFRACWAGE.cpp"
    "LawChangeBPMINCONST.cpp"
    "LawChangeBPSPECRATE.cpp"
    "LawChangeCHILDCARECREDIT.cpp"
    "LawChangeCHILDCAREDROPOUT.cpp"
    "LawChangeCOLACHANGE.cpp"
    "LawChangeDECLINEPERC.cpp"
    "LawChangeDROPOUTCHG.cpp"
    "LawChangeMARRLENGTH.cpp"
    "LawChangeNEWFORMULA.cpp"
    "LawChangeNEWSPECMIN.cpp"
    "LawChangeNRACHANGE.cpp"
    "LawChangeOut.cpp"
    "LawChangePSAACCT.cpp"
    "LawChangeRead.cpp"
    "LawChangeTAXBENCHG.cpp"
    "LawChangeTAXRATECHG.cpp"
    "LawChangeWAGEBASECHG.cpp"
    "LawChangeWIDFACTOR.cpp"
    "LawChangeWIFEFACTOR.cpp"
    "LawChangeWrite.cpp"
    "msdates.cpp"
    "msdatesvec.cpp"
    "oldpia.cpp"
    "oldstart.cpp"
    "OldStartLC.cpp"
    "pebs.cpp"
    "percmfb.cpp"
    "percpia.cpp"
    "PercPiaOut.cpp"
    "piacal.cpp"
    "piacalany.cpp"
    "piacallc.cpp"
    "PiaCalPL.cpp"
    "piadata.cpp"
    "PiadataArray.cpp"
    "PiaMethod.cpp"
    "PiaParamsLCTR.cpp"
    "PiaParamsTR.cpp"
    "piaparms.cpp"
    "piaparmsAny.cpp"
    "piaparmsLC.cpp"
    "piaparmsPL.cpp"
    "piaread.cpp"
    "piareadAny.cpp"
    "PiaTable.cpp"
    "PiaTableLC.cpp"
    "piawrite.cpp"
    "piawriteAny.cpp"
    "pib50mfb.cpp"
    "pib50pib.cpp"
    "pib52ame.cpp"
    "pib52mfb.cpp"
    "pib54ame.cpp"
    "pib54mfb.cpp"
    "pib54pia.cpp"
    "pib58ame.cpp"
    "pib58pib.cpp"
    "Pifc.cpp"
    "PortionAime.cpp"
    "PresValFacs.cpp"
    "Psa.cpp"
    "qc.cpp"
    "qcamt.cpp"
    "QcArray.cpp"
    "QcPacked.cpp"
    "railroad.cpp"
    "ReindWid.cpp"
    "ReindWidLC.cpp"
    "RetireTest.cpp"
    "rtgenrl.cpp"
    "ScaledEarnFactors.cpp"
    "Secondary.cpp"
    "SecondaryArray.cpp"
    "Sga.cpp"
    "SgaDerived.cpp"
    "SgaGeneral.cpp"
    "SpecMin.cpp"
    "SpecMinLC.cpp"
    "TaxBenefits.cpp"
    "TaxBenefitsLC.cpp"
    "TaxData.cpp"
    "TaxRates.cpp"
    "TaxRatesLC.cpp"
    "TaxRatesPL.cpp"
    "TransGuar.cpp"
    "TransGuarLC.cpp"
    "UserAssumptions.cpp"
    "WageBase.cpp"
    "WageInd.cpp"
    "WageIndGeneral.cpp"
    "WageIndLC.cpp"
    "WageIndNonFreeze.cpp"
    "wbgenrl.cpp"
    "wbgenrlLC.cpp"
    "WorkerDataArray.cpp"
    "WorkerDataGeneral.cpp"
    "wrkrdata.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_ANYPIABDEBUG   "piadata"
    TARGET_NAME_ANYPIABRELEASE "piadata"
    TARGET_NAME_ANYPIACDEBUG   "piadata"
    TARGET_NAME_ANYPIACRELEASE "piadata"
    TARGET_NAME_DEBUG          "piadata"
    TARGET_NAME_RELEASE        "piadata"
)

################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_ANYPIABDEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/Debug"
    OUTPUT_DIRECTORY_ANYPIABRELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Release"
    OUTPUT_DIRECTORY_ANYPIACDEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/Debug"
    OUTPUT_DIRECTORY_ANYPIACRELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Release"
    OUTPUT_DIRECTORY_DEBUG          "${CMAKE_CURRENT_SOURCE_DIR}/Debug"
    OUTPUT_DIRECTORY_RELEASE        "${CMAKE_CURRENT_SOURCE_DIR}/Release"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/..;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../windows;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../boost_1_64_0"
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Emscripten")
    set(CMAKE_CXX_FLAGS "-fdeclspec")
    
    ############
    # https://stackoverflow.com/questions/15724357/using-boost-with-emscripten
    ############
    #set_target_properties (${PROJECT_NAME} PROPERTIES 
    #COMPILE_FLAGS "-s USE_BOOST_HEADERS=1 -s DISABLE_EXCEPTION_CATCHING=0"
    #LINK_FLAGS "--bind --emrun -s TOTAL_MEMORY=500MB -s USE_BOOST_HEADERS=1 -s DISABLE_EXCEPTION_CATCHING=0"
    #)

else()
    set(CMAKE_CXX_FLAGS "/EHsc")
    #target_include_directories(${PROJECT_NAME} PUBLIC
    #    "${CMAKE_CURRENT_SOURCE_DIR}/../boost_1_64_0"
    #)
endif()

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:anypiabDebug>:"
        "_DEBUG"
    ">"
    "$<$<CONFIG:anypiabRelease>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:anypiacDebug>:"
        "_DEBUG"
    ">"
    "$<$<CONFIG:anypiacRelease>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:Debug>:"
        "_DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG"
    ">"
    "WIN32;"
    "_LIB;"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:anypiabDebug>:
            /Od;
            /RTC1;
            /MTd;
            /ZI
        >
        $<$<CONFIG:anypiabRelease>:
            /MT;
            /Zi
        >
        $<$<CONFIG:anypiacDebug>:
            /Od;
            /RTC1;
            /MTd;
            /ZI
        >
        $<$<CONFIG:anypiacRelease>:
            /MT;
            /Zi
        >
        $<$<CONFIG:Debug>:
            /Od;
            /RTC1;
            /MTd;
            /ZI
        >
        $<$<CONFIG:Release>:
            /MT;
            /Zi
        >
        /Gm;
        /W3;
        /GR;
        /wd4267;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
endif()