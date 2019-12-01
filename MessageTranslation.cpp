/**
 * @file MessageTranslation.cpp
 * @author Philip Zellweger (philip.zellweger@hsr.ch)
 * @brief Serializing functions for the messagetypes
 * @version 0.1
 * @date 2019-11-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "MessageTranslation.h"

// global defined translate function
    // TODO storage problem 

static void *translateJsonToStruct(byte* payload, unsigned int length, bufferStruct &buffer)
{
    // Deserialize json object to json document
    DynamicJsonDocument tempJson(length);
    DeserializationError error = deserializeJson(doc, json);

    switch (tempJson["msgType"].as<unsigned int>())
    {
    case MessageType::Package:
        return ParsePackageMessage::parseJSONToStruct(doc, error);
        break;
    case MessageType::Error:
        return ParseErrorMessage::parseJSONToStruct(doc, error);
        break;
    case MessageType::SBAvailable:
        return ParseSBAvailableMessage::parseJSONToStruct(doc, error);
        break;
    case MessageType::SBPosition:
        return ParseSBPositionMessage::parseJSONToStruct(doc, error);
        break;
    case MessageType::SBState:
        return ParseSBStateMessage::parseJSONToStruct(doc, error);
        break;
    case MessageType::SBToSVHandshake:
        return ParseSBtoSVHandshakeMessage::parseJSONToStruct(doc, error);
        break;
    case MessageType::SVAvailable:
        return ParseSVAvailableMessage::parseJSONToStruct(doc, error);
        break;
    case MessageType::SVPosition:
        return ParseSVPositionMessage::parseJSONToStruct(doc, error);
        break;
    case MessageType::SVState:
        return ParseSVStateMessage::parseJSONToStruct(doc, error);
        break;
    case MessageType::SBToSOHandshake:
        return ParseSBtoSOHandshakeMessage::parseJSONToStruct(doc, error);
        break;
    case MessageType::SOPosition:
        return ParseSOPositionMessage::parseJSONToStruct(doc, error);
        break;
    case MessageType::SOState:
        return ParseSOStateMessage::parseJSONToStruct(doc, error);
        break;
    default:
        DBWARNING("Translation failed");
        break;
    }
}

template<typename T>
static String translateStructToString(const &T object)
{
    switch(object.msgType)
    {
    case Package:
        return ParsePackageMessage::parseStructToString(object);
        break;
    case Error:
        return ParseErrorMessage::parseStructToString(object);
        break;
    case SBAvailable:
        return ParseSBAvailableMessage::parseStructToString(object);
        break;
    case SBPosition:
        return ParseSBPositionMessage::parseStructToString(object);
        break;
    case SBState:
        return ParseSBStateMessage::parseStructToString(object);
        break;
    case SBToSVHandshake:
        return ParseSBtoSVHandshakeMessage::parseStructToString(object);
        break;
    case SVAvailable:
        return ParseSVAvailableMessage::parseStructToString(object);
        break;
    case SVPosition:
        return ParsSVPositionMessage::parseStructToString(object);
        break;
    case SVState:
        return ParseSVStateMessage::parseStructToString(object);
        break;
    case SBToSOHandshake:
        return ParseSBtoSOHandshakeMessage::parseStructToString(object);
        break;
    case SOPosition:
        return ParseSOPositionMessage::parseStructToString(object);
        break;
    case SOState:
        return ParseSOStateMessage::parseStructToString(object);
        break;
    default:
        DBWarning("Translation failed");
        return "Translation failed";
        break;
    }
}


// Message class
Message::Message()
{
}

Message::~Message()
{
}

// ParsePackageMessage class
ParsePackageMessage::ParsePackageMessage()
{
}

ParsePackageMessage::~ParsePackageMessage()
{
}

PackageMessage *ParsePackageMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("ParsePackageMessage::parseJSONToStruct(JsonDocument doc, &PackageMessage object, DeserializationError error)");
    PackageMessage *transObject = new PackageMessage;
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        transObject->msgFrame->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgFrage->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgFrage->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgFrage->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgFrage->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->packageId = doc["packageId"].as<unsigned int>();
        transObject->cargo = doc["cargo"].as<String>();
        transObject->targetDest = doc["targetDest"].as<String>;
        transObject->targetReg = doc["targetReg"].as<String>;

        // return dynamic object with pointer
        return transObject;
    }
}

String ParsePackageMessage::parseStructToString(const PackageMessage *object)
{
    DBFUNCCALLln("ParsePackageMessage::parseStructToString(const PackageMessage *object)");
    String tempString = "{\"packageId\":\"" + object.packageId"\",\"cargo\":\"" + object.cargo"\",\"targetDest\":\"" + object.targetDest"\",\"targetReg\":\"" + object.targetReg + "\"}");
    return tempString;    
}

void ParsePackageMessage::setMessage(PackageMessage &object, unsigned int messageId, Consignor messageConsignor, String messagePackageId, String messageCargo, String messageTargetDest, String messageTargetReg)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.packageId = messagePackageId;
    object.cargo = messageCargo;
    object.targetDest = messageTargetDest;
    object.targetReg = messageTargetReg;
}

// ParseErrorMessage class
ParseErrorMessage::ParseErrorMessage()
{
}

ParseErrorMessage::~ParseErrorMessage()
{
}

ErrorMessage *ParseErrorMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("ParseErrorMessage::parseJSONToStruct(JsonDocument doc, &ErrorMessage object, DeserializationError error)");
    ErrorMessage *transObject = new ErrorMessage;
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        transObject->msgFrame->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgFrage->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgFrage->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgFrage->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgFrage->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->error = doc["error"].as<bool>;
        transObject->token = doc["token"].as<bool>;

        // return dynamic object with pointer
        return transObject;
    }    
}

String ParseErrorMessage::parseStructToString(const ErrorMessage *object)
{
    DBFUNCCALLln("ParseErrorMessage::parseStructToString(const ErrorMessage *object)");
    String tempString = "{\"error\":\"" + object.error"\",\"token\":\"" + object.token + "\"}");
    return tempString;
}

void ParseErrorMessage::setMessage(ErrorMessage &object, unsigned int messageId, Consignor messageConsignor, bool messageError, bool messageToken)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.error = messageError;
    object.token = messageToken;
}

// ParseSBAvailableMessage class
ParseSBAvailableMessage::ParseSBAvailableMessage()
{
}

ParseSBAvailableMessage::~ParseSBAvailableMessage()
{
}

SBAvailableMessage *ParseSBAvailableMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("ParseSBAvailableMessage::parseJSONToStruct(JsonDocument doc, &SBAvailableMessage object, DeserializationError error)");
    SBAvailableMessage *transObject = new SBAvailableMessage;
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        transObject->msgFrame->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgFrage->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgFrage->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgFrage->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgFrage->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->sector = doc["sector"].as<String>;
        transObject->line = doc["line"].as<int>;
        transObject->targetReg = doc["targetReg"].as<String>;

        // return dynamic object with pointer
        return transObject;
    }           
}

String ParseSBAvailableMessage::parseStructToString(const SBAvailableMessage *object)
{
    DBFUNCCALLln("ParseSBAvailableMessage::parseStructToString(const ParseSBAvailableMessage *object)");
    String tempString = "{\"sector\":\"" + object.sector"\",\"line\":\"" + object.line"\",\"targetReg\":\"" + object.targetReg + "\"}");
    return tempString;    
}

void ParseSBAvailableMessage::setMessage(SBAvailableMessage &object, unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine, String messageTargetReg)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.sector = messageSector;
    object.line = messageLine;
    object.targetReg = messageTargetReg;
}

// ParseSBPositionMessage class
ParseSBPositionMessage::ParseSBPositionMessage()
{
}

ParseSBPositionMessage::~ParseSBPositionMessage()
{
}

SBPositionMessage *ParseSBPositionMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("ParseSBPositionMessage::parseJSONToStruct(JsonDocument doc, &SBPositionMessage object, DeserializationError error)");
    SBPositionMessage *transObject = new SBPositionMessage;
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        transObject->msgFrame->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgFrage->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgFrage->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgFrage->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgFrage->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->sector = doc["sector"].as<String>;
        transObject->line = doc["line"].as<int>;

        // return dynamic object with pointer
        return transObject;
    }       
}

String ParseSBPositionMessage::parseStructToString(const SBPositionMessage *object)
{
    DBFUNCCALLln("ParseSBPositionMessage::parseStructToString(const SBPositionMessage *object)");
    String tempString = "{\"sector\":\"" + object.sector"\",\"line\":\"" + object.line + "\"}");
    return tempString;    
}

void ParseSBPositionMessage::setMessage(SBPositionMessage &object, unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.sector = messageSector;
    object.line = messageLine;
}

// ParseSBStateMessage class
ParseSBStateMessage::ParseSBStateMessage()
{
}

ParseSBStateMessage::~ParseSBStateMessage()
{
}

SBStateMessage *ParseSBStateMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("ParseSBStateMessage::parseJSONToStruct(JsonDocument doc, &SBStateMessage object, DeserializationError error)");
    SBStateMessage *transObject = new SBStateMessage;
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        transObject->msgFrame->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgFrage->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgFrage->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgFrage->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgFrage->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->state = doc["state"].as<String>;

        // return dynamic object with pointer
        return transObject;
    }   
}

String ParseSBStateMessage::parseStructToString(const SBStateMessage *object)
{
    DBFUNCCALLln("ParseSBStateMessage::parseStructToString(const SBStateMessage *object)");
    String tempString = "{\"state\":\"" + object.state +"\"}");
    return tempString;    
}

void ParseSBStateMessage::setMessage(SBStateMessage &object, unsigned int messageId, Consignor messageConsignor, String messageState)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.state = messageState;
}

// ParseSBtoSVHandshakeMessage class
ParseSBtoSVHandshakeMessage::ParseSBtoSVHandshakeMessage()
{
}

ParseSBtoSVHandshakeMessage::~ParseSBtoSVHandshakeMessage()
{
}

SBToSVHandshakeMessage *ParseSBtoSVHandshakeMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("ParseSBtoSVHandshakeMessage::parseJSONToStruct(JsonDocument doc, &SBToSVHandshakeMessage object, DeserializationError error)");
    SBToSVHandshakeMessage *transObject = new SBToSVHandshakeMessage;
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        transObject->msgFrame->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgFrage->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgFrage->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgFrage->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgFrage->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->reck = doc["reck"].as<String>;
        transObject->ack = doc["ack"].as<String>;
        transObject->cargo = doc["cargo"]<String>;
        transObject->line = doc["line"]<int>;

        // return dynamic object with pointer
        return transObject;
    }       
}

String ParseSBtoSVHandshakeMessage::parseStructToString(const SBToSVHandshakeMessage *object)
{
    DBFUNCCALLln("ParseSBtoSVHandshakeMessage::parseStructToString(const SBToSVHandshakeMessage *object)");
    String tempString = "{\"reck\":\"" + object.reck"\",\"ack\":\"" + object.ack"\",\"cargo\":\"" + object.cargo"\",\"line\":\"" + object.line + "\"}");
    return tempString;    
}

void ParseSBtoSVHandshakeMessage::setMessage(SBToSVHandshakeMessage &object, unsigned int messageId, Consignor messageConsignor, String messageReck, String messageAck, String messageCargo, int messageLine)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.reck = messageReck;
    object.ack = messageAck;
    object.cargo = messageCargo;
    object.line = messageLine;
}

// ParseSVAvailableMessage class
ParseSVAvailableMessage::ParseSVAvailableMessage()
{
}

ParseSVAvailableMessage::~ParseSVAvailableMessage()
{
}

SVAvailableMessage *ParseSVAvailableMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("ParseSVAvailableMessage::parseJSONToStruct(JsonDocument doc, &SVAvailableMessage object, DeserializationError error)");
    SVAvailableMessage *transObject = new SVAvailableMessage;
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        transObject->msgFrame->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgFrage->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgFrage->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgFrage->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgFrage->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->sector = doc["sector"].as<String>;
        transObject->line = doc["line"].as<int>;

        // return dynamic object with pointer
        return transObject;
    }       
}

String ParseSVAvailableMessage::parseStructToString(const SVAvailableMessage *object)
{
    DBFUNCCALLln("ParseSVAvailableMessage::parseStructToString(const SVAvailableMessage *object)");
    String tempString = "{\"sector\":\"" + object.sector"\",\"line\":\"" + object.line + "\"}");
    return tempString;    
}

void ParseSVAvailableMessage::setMessage(SVAvailableMessage &object, unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.sector = messageSector;
    object.line = messageLine;
}

// ParseSVPositionMessage class
ParseSVPositionMessage::ParseSVPositionMessage()
{
}

ParseSVPositionMessage::~ParseSVPositionMessage()
{
}

SVPositionMessage *ParseSVPositionMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("ParseSVPositionMessage::parseJSONToStruct(JsonDocument doc, &SVPositionMessage object, DeserializationError error)");
    SVPositionMessage *transObject = new SVPositionMessage;
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        transObject->msgFrame->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgFrage->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgFrage->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgFrage->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgFrage->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->sector = doc["sector"].as<String>;
        transObject->line = doc["line"].as<int>;

        // return dynamic object with pointer
        return transObject;
    }
}

String ParseSVPositionMessage::parseStructToString(const SVPositionMessage *object)
{
    DBFUNCCALLln("ParseSVPositionMessage::parseStructToString(const SVPositionMessage *object)");
    String tempString = "{\"sector\":\"" + object.sector"\",\"line\":\"" + object.line + "\"}");
    return tempString;    
}

void ParseSVPositionMessage::setMessage(SVPositionMessage &object, unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.sector = messageSector;
    object.line = messageLine;
}

// ParseSVStateMessage class
ParseSVStateMessage::ParseSVStateMessage()
{
}

ParseSVStateMessage::~ParseSVStateMessage()
{
}

SVStateMessage *ParseSVStateMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{   
    DBFUNCCALLln("ParseSVStateMessage::parseJSONToStruct(JsonDocument doc, &SVStateMessage object, DeserializationError error)");
    SVStateMessage *transObject = new SVStateMessage;
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        transObject->msgFrame->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgFrage->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgFrage->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgFrage->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgFrage->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->state = doc["state"].as<String>;

        // return dynamic object with pointer
        return transObject;
    }
}

String ParseSVStateMessage::parseStructToString(const SVStateMessage *object)
{
    DBFUNCCALLln("ParseSVStateMessage::parseStructToString(const SVStateMessage *object)");
    String tempString = "{\"state\":\"" + object.state "\"}");
    return tempString;    
}

void ParseSVStateMessage::setMessage(SVStateMessage &object, unsigned int messageId, Consignor messageConsignor, String messageState)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.state = messageState;
}

// ParseSBtoSOHandshakeMessage class
ParseSBtoSOHandshakeMessage::ParseSBtoSOHandshakeMessage()
{
}

ParseSBtoSOHandshakeMessage::~ParseSBtoSOHandshakeMessage()
{
}

SBtoSOHandshakeMessage *ParseSBtoSOHandshakeMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{   
    DBFUNCCALLln("ParseSBtoSOHandshakeMessage::parseJSONToStruct(JsonDocument doc, &SBtoSOHandshakeMessage object, DeserializationError error)");
    SBtoSOHandshakeMessage *transObject = new SBtoSOHandshakeMessage;
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        transObject->msgFrame->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgFrage->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgFrage->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgFrage->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgFrage->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->reck = doc["reck"].as<String>;
        transObject->ack = doc["ack"].as<String>;
        transObject->cargo = doc["cargo"].as<String>;
        transObject->targetReg = doc["targetReg"].as<String>;
        transObject->line = doc["line"].as<int>;

        // return dynamic object with pointer
        return transObject;
    }
}

String ParseSBtoSOHandshakeMessage::parseStructToString(const SBtoSOHandshakeMessage *object)
{
    DBFUNCCALLln("ParseSBtoSOHandshakeMessage::parseStructToString(const SBtoSOHandshakeMessage *object)");
    String tempString = "{\"reck\":\"" + object.reck"\",\"ack\":\"" + object.ack"\",\"cargo\":\"" + object.cargo"\",\"targetReg\":\"" + object.targetReg"\",\"line\":\"" + object.line + "\"}");
    return tempString;    
}

void ParseSBtoSOHandshakeMessage::setMessage(SBtoSOHandshakeMessage &object, unsigned int messageId, Consignor messageConsignor, String messageReck, String messageAck, String messageCargo, String messageTargetReg, int messageLine)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.reck = messageReck;
    object.ack = messageAck;
    object.cargo = messageCargo;
    object.targetReg = messageTargetReg;
    object.line = messageLine;
}

// ParseSOPositionMessage class
ParseSOPositionMessage::ParseSOPositionMessage()
{
}

ParseSOPositionMessage::~ParseSOPositionMessage()
{
}

void ParseSOPositionMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{   
    DBFUNCCALLln("ParseSOPositionMessage::parseJSONToStruct(JsonDocument doc, &SOPositionMessage object, DeserializationError error)");
    SOPositionMessage *transObject = new SOPositionMessage;
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        transObject->msgFrame->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgFrage->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgFrage->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgFrage->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgFrage->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->line = doc["line"].as<int>;

        // return dynamic object with pointer
        return transObject;
    }
}

String ParseSOPositionMessage::parseStructToString(const SOPositionMessage *object)
{
    DBFUNCCALLln("ParseSOPositionMessage::parseStructToString(const SOPositionMessage *object)");
    String tempString = "{\"line\":\"" + object.line "\"}");
    return tempString;    
}

void ParseSOPositionMessage::setMessage(SOPositionMessage &object, unsigned int messageId, Consignor messageConsignor, int messageLine)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.line = messageLine;
}

// ParseSOStateMessage class
ParseSOStateMessage::ParseSOStateMessage()
{
}

ParseSOStateMessage::~ParseSOStateMessage()
{
}

SOStateMessage *ParseSOStateMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{   
    DBFUNCCALLln("ParseSOStateMessage::parseJSONToStruct(JsonDocument doc, &SOStateMessage object, DeserializationError error)");
    SOStateMessage *transObject = new SOStateMessage;
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        transObject->msgFrame->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgFrage->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgFrage->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgFrage->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgFrage->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->state = doc["state"].as<String>;

        // return dynamic object with pointer
        return transObject;
    }
}

String ParseSOStateMessage::parseStructToString(const SOStateMessage *object)
{
    DBFUNCCALLln("ParseSOStateMessage::parseStructToString(const SOStateMessage *object)");
    String tempString = "{\"state\":\"" + object.state "\"}");
    return tempString;    
}

void ParseSOStateMessage::setMessage(SOStateMessage &object, unsigned int messageId, Consignor messageConsignor, String messageState)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.state = messageState;
}