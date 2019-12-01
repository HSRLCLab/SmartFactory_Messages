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
static MessageFrame *translateJsonToStruct(byte* payload, unsigned int length, bufferStruct &buffer)
{
    // Deserialize json object to json document
    DynamicJsonDocument tempJson(length);
    DeserializationError error = deserializeJson(doc, json);

    // Generate pointer to return dynamic object
    MessageFrame *translationPtr = nullptr;

    switch (tempJson["msgType"].as<unsigned int>())
    {
    case MessageType::Package:
        ParsePackageMessage parser = new ParsePackageMessage;
        translationPtr = parser.parseJSONToStruct(doc, error);
        delete parser;
        return translationPtr;
        break;
    case MessageType::Error:
        ParseErrorMessage parser = new ParseErrorMessage;
        translationPtr = parser.parseJSONToStruct(doc, error);
        delete parser;
        return translationPtr;
        break;
    case MessageType::SBAvailable:
        ParseSBAvailableMessage parser = new ParseSBAvailableMessage;
        translationPtr = parser.parseJSONToStruct(doc, error);
        delete parser;
        return translationPtr;
        break;
    case MessageType::SBPosition:
        ParseSBPositionMessage parser = new ParseSBPositionMessage;
        translationPtr = parser.parseJSONToStruct(doc, error);
        delete parser;
        return translationPtr;
        break;
    case MessageType::SBState:
        ParseSBStateMessage parser = new ParseSBStateMessage;
        translationPtr = parser.parseJSONToStruct(doc, error);
        delete parser;
        return translationPtr;
        break;
    case MessageType::SBToSVHandshake:
        ParseSBtoSVHandshakeMessage parser = new ParseSBtoSVHandshakeMessage;
        translationPtr = parser.parseJSONToStruct(doc, error);
        delete parser;
        return translationPtr;
        break;
    case MessageType::SVAvailable:
        ParseSVAvailableMessage parser = new ParseSVAvailableMessage;
        translationPtr = parser.parseJSONToStruct(doc, error);
        delete parser;
        return translationPtr;
        break;
    case MessageType::SVPosition:
        ParseSVPositionMessage parser = new ParseSVPositionMessage;
        translationPtr = parser.parseJSONToStruct(doc, error);
        delete parser;
        return translationPtr;
        break;
    case MessageType::SVState:
        ParseSVStateMessage parser = new ParseSVStateMessage;
        translationPtr = parser.parseJSONToStruct(doc, error);
        delete parser;
        return translationPtr;
        break;
    case MessageType::SBToSOHandshake:
        ParseSBtoSOHandshakeMessage parser = new ParseSBtoSOHandshakeMessage;
        translationPtr = parser.parseJSONToStruct(doc, error);
        delete parser;
        return translationPtr;
        break;
    case MessageType::SOPosition:
        ParseSOPositionMessage parser = new ParseSOPositionMessage;
        translationPtr = parser.parseJSONToStruct(doc, error);
        delete parser;
        return translationPtr;
        break;
    case MessageType::SOState:
        ParseSOStateMessage parser = new ParseSOStateMessage;
        translationPtr = parser.parseJSONToStruct(doc, error);
        delete parser;
        return translationPtr;
        break;
    default:
        DBWARNING("Translation failed");
        break;
    }
}

static String translateStructToString(MessageFrame const &object)
{
    String translationString;
    switch(object.msgType)
    {
    case MessageType::Package:
        ParsePackageMessage parser = new ParsePackageMessage;
        translationString = parser.parseStructToString(object);
        delete parser;
        return translationString;
        break;
    case MessageType::Error:
        ParseErrorMessage parser = new ParseErrorMessage;
        translationString = parser.parseStructToString(object);
        delete parser;
        return translationString;
        break;
    case MessageType::SBAvailable:
        ParseSBAvailableMessage parser = new ParseSBAvailableMessage;
        translationString = parser.parseStructToString(object);
        delete parser;
        return translationString;
        break;
    case MessageType::SBPosition:
        ParseSBPositionMessage parser = new ParseSBPositionMessage;
        translationString = parser.parseStructToString(object);
        delete parser;
        return translationString;
        break;
    case MessageType::SBState:
        ParseSBStateMessage parser = new ParseSBStateMessage;
        translationString = parser.parseStructToString(object);
        delete parser;
        return translationString;
        break;
    case MessageType::SBToSVHandshake:
        ParseSBtoSVHandshakeMessage parser = new ParseSBtoSVHandshakeMessage;
        translationString = parser.parseStructToString(object);
        delete parser;
        return translationString;
        break;
    case MessageType::SVAvailable:
        ParseSVAvailableMessage parser = new ParseSVAvailableMessage;
        translationString = parser.parseStructToString(object);
        delete parser;
        return translationString;
        break;
    case MessageType::SVPosition:
        ParsSVPositionMessage parser = new ParsSVPositionMessage;
        translationString = parser.parseStructToString(object);
        delete parser;
        return translationString;
        break;
    case MessageType::SVState:
        ParseSVStateMessage parser = new ParseSVStateMessage;
        translationString = parser.parseStructToString(object);
        delete parser;
        return translationString;
        break;
    case MessageType::SBToSOHandshake:
        ParseSBtoSOHandshakeMessage parser = new ParseSBtoSOHandshakeMessage;
        translationString = parser.parseStructToString(object);
        delete parser;
        return translationString;
        break;
    case MessageType::SOPosition:
        ParseSOPositionMessage parser = new ParseSOPositionMessage;
        translationString = parser.parseStructToString(object);
        delete parser;
        return translationString;
        break;
    case MessageType::SOState:
        ParseSOStateMessage parser = new ParseSOStateMessage;
        translationString = parser.parseStructToString(object);
        delete parser;
        return translationString;
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
        transObject->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->packageId = doc["packageId"].as<unsigned int>();
        transObject->cargo = doc["cargo"].as<String>();
        transObject->targetDest = doc["targetDest"].as<String>;
        transObject->targetReg = doc["targetReg"].as<String>;

        // return dynamic object with pointer
        return transObject;
    }
}

String ParsePackageMessage::parseStructToString(MessageFrame const &object)
{
    DBFUNCCALLln("ParsePackageMessage::parseStructToString(const PackageMessage *object)");
    String tempString = "{\"msgId\":\"" + (String)object.msgId + "\",\"msgType\":\"" + (String)object.msgType + "\",\"msgLength\":\"" + (String)object.msgLength + "\",\"msgConsignor\":\"" + (String)object.msgConsignor + "\",\"packageId\":\"" + (String)object.packageId + "\",\"cargo\":\"" + object.cargo + "\",\"targetDest\":\"" + object.targetDest + "\",\"targetReg\":\"" + object.targetReg + "\"}");
    return tempString;    
}

void ParsePackageMessage::setMessage(MessageFrame &object, unsigned int messageId, Consignor messageConsignor, String messagePackageId, String messageCargo, String messageTargetDest, String messageTargetReg)
{
    object.msgId = messageId;
    object.msgConsignor = messageConsignor;
    object.packageId = messagePackageId;
    object.cargo = messageCargo;
    object.targetDest = messageTargetDest;
    object.targetReg = messageTargetReg;
    object.msgLength = sizeof(object);
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
        transObject->>msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->error = doc["error"].as<bool>;
        transObject->token = doc["token"].as<bool>;

        // return dynamic object with pointer
        return transObject;
    }    
}

String ParseErrorMessage::parseStructToString(MessageFrame const &object)
{
    DBFUNCCALLln("ParseErrorMessage::parseStructToString(const ErrorMessage *object)");
    String tempString = "{\"msgId\":\"" + (String)object.msgId + "\",\"msgType\":\"" + (String)object.msgType + "\",\"msgLength\":\"" + (String)object.msgLength + "\",\"msgConsignor\":\"" + (String)object.msgConsignor + "\",\"error\":\"" + (String)object.error + "\",\"token\":\"" + (String)object.token + "\"}");
    return tempString;
}

void ParseErrorMessage::setMessage(MessageFrame &object, unsigned int messageId, Consignor messageConsignor, bool messageError, bool messageToken)
{
    object.msgId = messageId;
    object.msgConsignor = messageConsignor;
    object.error = messageError;
    object.token = messageToken;
    object.msgLength = sizeof(object);
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
        transObject->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->sector = doc["sector"].as<String>;
        transObject->line = doc["line"].as<int>;
        transObject->targetReg = doc["targetReg"].as<String>;

        // return dynamic object with pointer
        return transObject;
    }           
}

String ParseSBAvailableMessage::parseStructToString(MessageFrame const &object)
{
    DBFUNCCALLln("ParseSBAvailableMessage::parseStructToString(const ParseSBAvailableMessage *object)");
    String tempString = "{\"msgId\":\"" + (String)object.msgId + "\",\"msgType\":\"" + (String)object.msgType + "\",\"msgLength\":\"" + (String)object.msgLength + "\",\"msgConsignor\":\"" + (String)object.msgConsignor + "\",\"sector\":\"" + object.sector + "\",\"line\":\"" + (String)object.line + "\",\"targetReg\":\"" + object.targetReg + "\"}");
    return tempString;    
}

void ParseSBAvailableMessage::setMessage(MessageFrame &object, unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine, String messageTargetReg)
{
    object.msgId = messageId;
    object.msgConsignor = messageConsignor;
    object.sector = messageSector;
    object.line = messageLine;
    object.targetReg = messageTargetReg;
    object.msgLength = sizeof(object);
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
        transObject->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->sector = doc["sector"].as<String>;
        transObject->line = doc["line"].as<int>;

        // return dynamic object with pointer
        return transObject;
    }       
}

String ParseSBPositionMessage::parseStructToString(MessageFrame const &object)
{
    DBFUNCCALLln("ParseSBPositionMessage::parseStructToString(const SBPositionMessage *object)");
    String tempString = "{\"msgId\":\"" + (String)object.msgId + "\",\"msgType\":\"" + (String)object.msgType + "\",\"msgLength\":\"" + (String)object.msgLength + "\",\"msgConsignor\":\"" + (String)object.msgConsignor + "\",\"sector\":\"" + object.sector + "\",\"line\":\"" + (String)object.line + "\"}");
    return tempString;    
}

void ParseSBPositionMessage::setMessage(MessageFrame &object, unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine)
{
    object.msgId = messageId;
    object.msgConsignor = messageConsignor;
    object.sector = messageSector;
    object.line = messageLine;
    object.messageLength = sizeof(object);
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
        transObject->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->state = doc["state"].as<String>;

        // return dynamic object with pointer
        return transObject;
    }   
}

String ParseSBStateMessage::parseStructToString(MessageFrame const &object)
{
    DBFUNCCALLln("ParseSBStateMessage::parseStructToString(const SBStateMessage *object)");
    String tempString = "{\"msgId\":\"" + (String)object.msgId + "\",\"msgType\":\"" + (String)object.msgType + "\",\"msgLength\":\"" + (String)object.msgLength + "\",\"msgConsignor\":\"" + (String)object.msgConsignor + "\",\"state\":\"" + object.state +"\"}");
    return tempString;    
}

void ParseSBStateMessage::setMessage(MessageFrame &object, unsigned int messageId, Consignor messageConsignor, String messageState)
{
    object.msgId = messageId;
    object.msgConsignor = messageConsignor;
    object.state = messageState;
    object.messageLength = sizeof(object);
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
        transObject->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->reck = doc["reck"].as<String>;
        transObject->ack = doc["ack"].as<String>;
        transObject->cargo = doc["cargo"]<String>;
        transObject->line = doc["line"]<int>;

        // return dynamic object with pointer
        return transObject;
    }       
}

String ParseSBtoSVHandshakeMessage::parseStructToString(MessageFrame const &object)
{
    DBFUNCCALLln("ParseSBtoSVHandshakeMessage::parseStructToString(const SBToSVHandshakeMessage *object)");
    String tempString = "{\"msgId\":\"" + (String)object.msgId + "\",\"msgType\":\"" + (String)object.msgType + "\",\"msgLength\":\"" + (String)object.msgLength + "\",\"msgConsignor\":\"" + (String)object.msgConsignor + "\",\"reck\":\"" + object.reck + "\",\"ack\":\"" + object.ack + "\",\"cargo\":\"" + object.cargo + "\",\"line\":\"" + (String)object.line + "\"}");
    return tempString;    
}

void ParseSBtoSVHandshakeMessage::setMessage(MessageFrame &object, unsigned int messageId, Consignor messageConsignor, String messageReck, String messageAck, String messageCargo, int messageLine)
{
    object.msgId = messageId;
    object.msgConsignor = messageConsignor;
    object.reck = messageReck;
    object.ack = messageAck;
    object.cargo = messageCargo;
    object.line = messageLine;
    object.length = sizeof(object);
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
        transObject->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->sector = doc["sector"].as<String>;
        transObject->line = doc["line"].as<int>;

        // return dynamic object with pointer
        return transObject;
    }       
}

String ParseSVAvailableMessage::parseStructToString(MessageFrame const &object)
{
    DBFUNCCALLln("ParseSVAvailableMessage::parseStructToString(const SVAvailableMessage *object)");
    String tempString = "{\"msgId\":\"" + (String)object.msgId + "\",\"msgType\":\"" + (String)object.msgType + "\",\"msgLength\":\"" + (String)object.msgLength + "\",\"msgConsignor\":\"" + (String)object.msgConsignor + "\",\"sector\":\"" + object.sector + "\",\"line\":\"" + (String)object.line + "\"}");
    return tempString;    
}

void ParseSVAvailableMessage::setMessage(MessageFrame &object, unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine)
{
    object.msgId = messageId;
    object.msgConsignor = messageConsignor;
    object.sector = messageSector;
    object.line = messageLine;
    object.msgLength = sizeof(object);
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
        transObject->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->sector = doc["sector"].as<String>;
        transObject->line = doc["line"].as<int>;

        // return dynamic object with pointer
        return transObject;
    }
}

String ParseSVPositionMessage::parseStructToString(MessageFrame const &object)
{
    DBFUNCCALLln("ParseSVPositionMessage::parseStructToString(const SVPositionMessage *object)");
    String tempString = "{\"msgId\":\"" + (String)object.msgId + "\",\"msgType\":\"" + (String)object.msgType + "\",\"msgLength\":\"" + (String)object.msgLength + "\",\"msgConsignor\":\"" + (String)object.msgConsignor + "\",\"sector\":\"" + object.sector + "\",\"line\":\"" + (String)object.line + "\"}");
    return tempString;    
}

void ParseSVPositionMessage::setMessage(MessageFrame &object, unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine)
{
    object.msgId = messageId;
    object.msgConsignor = messageConsignor;
    object.sector = messageSector;
    object.line = messageLine;
    object.msgLength = sizeof(object);
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
        transObject->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->state = doc["state"].as<String>;

        // return dynamic object with pointer
        return transObject;
    }
}

String ParseSVStateMessage::parseStructToString(MessageFrame const &object)
{
    DBFUNCCALLln("ParseSVStateMessage::parseStructToString(const SVStateMessage *object)");
    String tempString = "{\"msgId\":\"" + (String)object.msgId + "\",\"msgType\":\"" + (String)object.msgType + "\",\"msgLength\":\"" + (String)object.msgLength + "\",\"msgConsignor\":\"" + (String)object.msgConsignor + "\",\"state\":\"" + object.state + "\"}");
    return tempString;    
}

void ParseSVStateMessage::setMessage(MessageFrame &object, unsigned int messageId, Consignor messageConsignor, String messageState)
{
    object.msgId = messageId;
    object.msgConsignor = messageConsignor;
    object.state = messageState;
    object.msgLength = sizeof(object);
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
        transObject->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgConsignor = doc["msgConsignor"].as<unsigned int>();

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

String ParseSBtoSOHandshakeMessage::parseStructToString(MessageFrame const &object)
{
    DBFUNCCALLln("ParseSBtoSOHandshakeMessage::parseStructToString(const SBtoSOHandshakeMessage *object)");
    String tempString = "{\"msgId\":\"" + (String)object.msgId + "\",\"msgType\":\"" + (String)object.msgType + "\",\"msgLength\":\"" + (String)object.msgLength + "\",\"msgConsignor\":\"" + (String)object.msgConsignor + "\",\"reck\":\"" + object.reck"\",\"ack\":\"" + object.ack + "\",\"cargo\":\"" + object.cargo + "\",\"targetReg\":\"" + object.targetReg + "\",\"line\":\"" + (String)object.line + "\"}");
    return tempString;    
}

void ParseSBtoSOHandshakeMessage::setMessage(MessageFrame &object, unsigned int messageId, Consignor messageConsignor, String messageReck, String messageAck, String messageCargo, String messageTargetReg, int messageLine)
{
    object.msgId = messageId;
    object.msgConsignor = messageConsignor;
    object.reck = messageReck;
    object.ack = messageAck;
    object.cargo = messageCargo;
    object.targetReg = messageTargetReg;
    object.line = messageLine;
    object.msgLength = sizeof(object);
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
        transObject->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->line = doc["line"].as<int>;

        // return dynamic object with pointer
        return transObject;
    }
}

String ParseSOPositionMessage::parseStructToString(MessageFrame const &object)
{
    DBFUNCCALLln("ParseSOPositionMessage::parseStructToString(const SOPositionMessage *object)");
    String tempString = "{\"msgId\":\"" + (String)object.msgId + "\",\"msgType\":\"" + (String)object.msgType + "\",\"msgLength\":\"" + (String)object.msgLength + "\",\"msgConsignor\":\"" + (String)object.msgConsignor + "\",\"line\":\"" + (String)object.line + "\"}");
    return tempString;    
}

void ParseSOPositionMessage::setMessage(MessageFrame &object, unsigned int messageId, Consignor messageConsignor, int messageLine)
{
    object.msgId = messageId;
    object.msgConsignor = messageConsignor;
    object.line = messageLine;
    object.msgLength = sizeof(object);
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
        transObject->msgId = 0;
    }
    else
    {
        // Parse message frame
        transObject->msgId = doc["msgId"].as<unsigned int>();
        transObject->msgType = doc["msgType"].as<unsigned int>();
        transObject->msgLength = doc["msgLength"].as<unsigned int>();
        transObject->msgConsignor = doc["msgConsignor"].as<unsigned int>();

        // Parse specific message
        transObject->state = doc["state"].as<String>;

        // return dynamic object with pointer
        return transObject;
    }
}

String ParseSOStateMessage::parseStructToString(MessageFrame const &object)
{
    DBFUNCCALLln("ParseSOStateMessage::parseStructToString(const SOStateMessage *object)");
    String tempString = "{\"msgId\":\"" + (String)object.msgId + "\",\"msgType\":\"" + (String)object.msgType + "\",\"msgLength\":\"" + (String)object.msgLength + "\",\"msgConsignor\":\"" + (String)object.msgConsignor + "\",\"state\":\"" + object.state + "\"}");
    return tempString;    
}

void ParseSOStateMessage::setMessage(MessageFrame &object, unsigned int messageId, Consignor messageConsignor, String messageState)
{
    object.msgId = messageId;
    object.msgConsignor = messageConsignor;
    object.state = messageState;
    object.msgLength = sizeof(object);
}