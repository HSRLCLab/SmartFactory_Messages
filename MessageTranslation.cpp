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
static void translateJsonToStruct(char* topic, byte* payload, unsigned int length)
{
    DynamicJsonDocument tempJson(length);
    DeserializationError error = deserializeJson(doc, json);     
    messageType tempMsgType = tempJson["msgType"].as<unsigned int>();
    unsigned int tempMsgId = tempJson["msgId"].as<unsigned int>();
    unsigned int tempMsgConsignor = tempJson["consignor"].as<unsigned int>;
    switch (tempMsgType)
    {
    case Package:
        PackageMessage TransObject = new PackageMessage;
        ParsePackageMessage::parseJSONToStruct(doc, TransObject, error);
        packageMessageBuffer = TransObject;
        delete TransObject;
        break;
    case Error:
        ErrorMessage TransObject = new ErrorMessage;
        ParseErrorMessage::parseJSONToStruct(doc, TransObject, error);
        errorMessageBuffer = TransObject;
        delete TransObject;
        break;
    case SBAvailable:
        SBAvailableMessage TransObject = new SBAvailableMessage;
        ParseSBAvailableMessage::parseJSONToStruct(doc, TransObject, error);
        availableMessageBuffer[tempMsgConsignor - 1] = TransObject;
        delete TransObject;
        break;
    case SBPosition:
        SBPositionMessage TransObject = new SBPositionMessage;
        ParseSBPositionMessage::parseJSONToStruct(doc, TransObject, error);
        positionMessageBuffer = TransObject;
        delete TransObject;
        break;
    case SBState:
        SBStateMessage TransObject = new SBStateMessage;
        ParseSBStateMessage::parseJSONToStruct(doc, TransObject, error);
        stateMessageBuffer = TransObject;
        delete TransObject;
        break;
    case SBToSVHandshake:
        SBToSVHandshakeMessage TransObject = new SBToSVHandshakeMessage;
        ParseSBtoSVHandshakeMessage::parseJSONToStruct(doc, TransObject, error);
        handshakeMessageSBToSVBuffer = TransObject;
        delete TransObject;
        break;
    case SVAvailable:
        SVAvailableMessage TransObject = new SVAvailableMessage;
        ParseSVAvailableMessage::parseJSONToStruct(doc, TransObject, error);
        availableMessageBuffer[tempMsgConsignor - 3] = TransObject;
        delete TransObject;
        break;
    case SVPosition:
        SVPositionMessage TransObject = new SVPositionMessage;
        ParseSVPositionMessage::parseJSONToStruct(doc, TransObject, error);
        svPositionMessageBuffer = TransObject;
        delete TransObject;
        break;
    case SVState:
        SVStateMessage TransObject = new SVStateMessage;
        ParseSVStateMessage::parseJSONToStruct(doc, TransObject, error);
        svStateMessageBuffer = TransObject;
        delete TransObject;
        break;
    case SBToSOHandshake:
        SBtoSOHandshakeMessage TransObject = new SBtoSOHandshakeMessage;
        ParseSBtoSOHandshakeMessage::parseJSONToStruct(doc, TransObject, error);
        handshakeMessageSBToSOBuffer = TransObject;
        delete TransObject;
        break;
    case SOPosition:
        SOPositionMessage TransObject = new SOPositionMessage;
        ParseSOPositionMessage::parseJSONToStruct(doc, TransObject, error);
        soPositionMessageBuffer = TransObject;
        delete TransObject;
        break;
    case SOState:
        SOStateMessage TransObject = new SOStateMessage;
        ParseSOStateMessage::parseJSONToStruct(doc, TransObject, error);
        soStateMessageBuffer = TransObject;
        delete TransObject;
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

void ParsePackageMessage::parseJSONToStruct(JsonDocument doc, &PackageMessage object, DeserializationError error)
{
    DBFUNCCALLln("ParsePackageMessage::parseJSONToStruct(JsonDocument doc, &PackageMessage object, DeserializationError error)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());
        object.packageId = "Parse failed";
    }
    else
    {
        object.packageId = doc["id"].as<String>();
        object.cargo = doc["cargo"].as<String>();
        object.targetDest = doc["targetDest"].as<String>;
        object.targetReg = doc["targetReg"].as<String>;
    }
}

String ParsePackageMessage::parseStructToString(const PackageMessage *object)
{
    DBFUNCCALLln("ParsePackageMessage::parseStructToString(const PackageMessage *object)");
    String tempString = "{\"packageId\":\"" + object.packageId"\",\"cargo\":\"" + object.cargo"\",\"targetDest\":\"" + object.targetDest"\",\"targetReg\":\"" + object.targetReg + "\"}");
    return tempString;    
}

void ParsePackageMessage::setMessage(PackageMessage &object, unsigned int messageId, Consignor messageConsignor, String messageTopic, String messagePackageId, String messageCargo, String messageTargetDest, String messageTargetReg)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.messageFrame.topic = messageTopic;
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

void ParseErrorMessage::parseJSONToStruct(JsonDocument doc, &ErrorMessage object, DeserializationError error)
{
    DBFUNCCALLln("ParseErrorMessage::parseJSONToStruct(JsonDocument doc, &ErrorMessage object, DeserializationError error)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());
        object.packageId = "Parse failed";
    }
    else
    {
        object.error = doc["error"].as<String>();
        object.token = doc["token"].as<String>();
    }    
}

String ParseErrorMessage::parseStructToString(const ErrorMessage *object)
{
    DBFUNCCALLln("ParseErrorMessage::parseStructToString(const ErrorMessage *object)");
    String tempString = "{\"error\":\"" + object.error"\",\"token\":\"" + object.token + "\"}");
    return tempString;
}

void ParseErrorMessage::setMessage(ErrorMessage &object, unsigned int messageId, Consignor messageConsignor, String messageTopic, bool messageError, bool messageToken)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.messageFrame.topic = messageTopic;
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

void ParseSBAvailableMessage::parseJSONToStruct(JsonDocument doc, &SBAvailableMessage object, DeserializationError error)
{
    DBFUNCCALLln("ParseSBAvailableMessage::parseJSONToStruct(JsonDocument doc, &SBAvailableMessage object, DeserializationError error)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());
        object.packageId = "Parse failed";
    }
    else
    {
        object.sector = doc["sector"].as<String>();
        object.line = doc["line"].as<String>();
        object.targetReg = doc["targetReg"].as<String>;
    }        
}

String ParseSBAvailableMessage::parseStructToString(const SBAvailableMessage *object)
{
    DBFUNCCALLln("ParseSBAvailableMessage::parseStructToString(const ParseSBAvailableMessage *object)");
    String tempString = "{\"sector\":\"" + object.sector"\",\"line\":\"" + object.line"\",\"targetReg\":\"" + object.targetReg + "\"}");
    return tempString;    
}

void ParseSBAvailableMessage::setMessage(SBAvailableMessage &object, unsigned int messageId, Consignor messageConsignor, String messageTopic, String messageSector, int messageLine, String messageTargetReg)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.messageFrame.topic = messageTopic;
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

void ParseSBPositionMessage::parseJSONToStruct(JsonDocument doc, &SBPositionMessage object, DeserializationError error)
{
    DBFUNCCALLln("ParseSBPositionMessage::parseJSONToStruct(JsonDocument doc, &SBPositionMessage object, DeserializationError error)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());
        object.packageId = "Parse failed";
    }
    else
    {
        object.sector = doc["sector"].as<String>();
        object.line = doc["line"].as<String>();
    }        
}

String ParseSBPositionMessage::parseStructToString(const SBPositionMessage *object)
{
    DBFUNCCALLln("ParseSBPositionMessage::parseStructToString(const SBPositionMessage *object)");
    String tempString = "{\"sector\":\"" + object.sector"\",\"line\":\"" + object.line + "\"}");
    return tempString;    
}

void ParseSBPositionMessage::setMessage(SBPositionMessage &object, unsigned int messageId, Consignor messageConsignor, String messageTopic, String messageSector, int messageLine)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.messageFrame.topic = messageTopic;
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

void ParseSBStateMessage::parseJSONToStruct(JsonDocument doc, &SBStateMessage object, DeserializationError error)
{
    DBFUNCCALLln("ParseSBStateMessage::parseJSONToStruct(JsonDocument doc, &SBStateMessage object, DeserializationError error)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());
        object.packageId = "Parse failed";
    }
    else
    {
        object.state = doc["state"].as<String>();
    }       
}

String ParseSBStateMessage::parseStructToString(const SBStateMessage *object)
{
    DBFUNCCALLln("ParseSBStateMessage::parseStructToString(const SBStateMessage *object)");
    String tempString = "{\"state\":\"" + object.state +"\"}");
    return tempString;    
}

void ParseSBStateMessage::setMessage(SBStateMessage &object, unsigned int messageId, Consignor messageConsignor, String messageTopic, String messageState)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.messageFrame.topic = messageTopic;
    object.state = messageState;
}

// ParseSBtoSVHandshakeMessage class
ParseSBtoSVHandshakeMessage::ParseSBtoSVHandshakeMessage()
{
}

ParseSBtoSVHandshakeMessage::~ParseSBtoSVHandshakeMessage()
{
}

void ParseSBtoSVHandshakeMessage::parseJSONToStruct(JsonDocument doc, &SBToSVHandshakeMessage object, DeserializationError error)
{
    DBFUNCCALLln("ParseSBtoSVHandshakeMessage::parseJSONToStruct(JsonDocument doc, &SBToSVHandshakeMessage object, DeserializationError error)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());
        object.packageId = "Parse failed";
    }
    else
    {
        object.reck = doc["reck"].as<String>;
        object.ack = doc["ack"].as<String>;
        object.cargo = doc["cargo"].as<String>;
        object.line = doc["line"].as<String>;
    }       
}

String ParseSBtoSVHandshakeMessage::parseStructToString(const SBToSVHandshakeMessage *object)
{
    DBFUNCCALLln("ParseSBtoSVHandshakeMessage::parseStructToString(const SBToSVHandshakeMessage *object)");
    String tempString = "{\"reck\":\"" + object.reck"\",\"ack\":\"" + object.ack"\",\"cargo\":\"" + object.cargo"\",\"line\":\"" + object.line + "\"}");
    return tempString;    
}

void ParseSBtoSVHandshakeMessage::setMessage(SBToSVHandshakeMessage &object, unsigned int messageId, Consignor messageConsignor, String messageTopic, String messageReck, String messageAck, String messageCargo, int messageLine)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.messageFrame.topic = messageTopic;
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

void ParseSVAvailableMessage::parseJSONToStruct(JsonDocument doc, &SVAvailableMessage object, DeserializationError error)
{
    DBFUNCCALLln("ParseSVAvailableMessage::parseJSONToStruct(JsonDocument doc, &SVAvailableMessage object, DeserializationError error)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());
        object.packageId = "Parse failed";
    }
    else
    {
        object.sector = doc["sector"].as<String>;
        object.line = doc["line"].as<String>;
    }       
}

String ParseSVAvailableMessage::parseStructToString(const SVAvailableMessage *object)
{
    DBFUNCCALLln("ParseSVAvailableMessage::parseStructToString(const SVAvailableMessage *object)");
    String tempString = "{\"sector\":\"" + object.sector"\",\"line\":\"" + object.line + "\"}");
    return tempString;    
}

void ParseSVAvailableMessage::setMessage(SVAvailableMessage &object, unsigned int messageId, Consignor messageConsignor, String messageTopic, String messageSector, int messageLine)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.messageFrame.topic = messageTopic;
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

void ParseSVPositionMessage::parseJSONToStruct(JsonDocument doc, &SVPositionMessage object, DeserializationError error)
{
    DBFUNCCALLln("ParseSVPositionMessage::parseJSONToStruct(JsonDocument doc, &SVPositionMessage object, DeserializationError error)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());
        object.packageId = "Parse failed";
    }
    else
    {
        object.sector = doc["sector"].as<String>;
        object.line = doc["line"].as<String>;
    }
}

String ParseSVPositionMessage::parseStructToString(const SVPositionMessage *object)
{
    DBFUNCCALLln("ParseSVPositionMessage::parseStructToString(const SVPositionMessage *object)");
    String tempString = "{\"sector\":\"" + object.sector"\",\"line\":\"" + object.line + "\"}");
    return tempString;    
}

void ParseSVPositionMessage::setMessage(SVPositionMessage &object, unsigned int messageId, Consignor messageConsignor, String messageTopic, String messageSector, int messageLine)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.messageFrame.topic = messageTopic;
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

void ParseSVStateMessage::parseJSONToStruct(JsonDocument doc, &SVStateMessage object, DeserializationError error)
{   
    DBFUNCCALLln("ParseSVStateMessage::parseJSONToStruct(JsonDocument doc, &SVStateMessage object, DeserializationError error)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());
        object.packageId = "Parse failed";
    }
    else
    {
        object.state = doc["sector"].as<String>;
    }
}

String ParseSVStateMessage::parseStructToString(const SVStateMessage *object)
{
    DBFUNCCALLln("ParseSVStateMessage::parseStructToString(const SVStateMessage *object)");
    String tempString = "{\"state\":\"" + object.state "\"}");
    return tempString;    
}

void ParseSVStateMessage::setMessage(SVStateMessage &object, unsigned int messageId, Consignor messageConsignor, String messageTopic, String messageState)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.messageFrame.topic = messageTopic;
    object.state = messageState;
}

// ParseSBtoSOHandshakeMessage class
ParseSBtoSOHandshakeMessage::ParseSBtoSOHandshakeMessage()
{
}

ParseSBtoSOHandshakeMessage::~ParseSBtoSOHandshakeMessage()
{
}

void ParseSBtoSOHandshakeMessage::parseJSONToStruct(JsonDocument doc, &SBtoSOHandshakeMessage object, DeserializationError error)
{   
    DBFUNCCALLln("ParseSBtoSOHandshakeMessage::parseJSONToStruct(JsonDocument doc, &SBtoSOHandshakeMessage object, DeserializationError error)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());
        object.packageId = "Parse failed";
    }
    else
    {
        object.reck = doc["reck"].as<String>;
        object.ack = doc["ack"].as<String>;
        object.cargo = doc["cargo"].as<String>;
        object.targetReg = doc["targetReg"].as<String>;
        object.line = doc["line"].as<int>;
    }
}

String ParseSBtoSOHandshakeMessage::parseStructToString(const SBtoSOHandshakeMessage *object)
{
    DBFUNCCALLln("ParseSBtoSOHandshakeMessage::parseStructToString(const SBtoSOHandshakeMessage *object)");
    String tempString = "{\"reck\":\"" + object.reck"\",\"ack\":\"" + object.ack"\",\"cargo\":\"" + object.cargo"\",\"targetReg\":\"" + object.targetReg"\",\"line\":\"" + object.line + "\"}");
    return tempString;    
}

void ParseSBtoSOHandshakeMessage::setMessage(SBtoSOHandshakeMessage &object, unsigned int messageId, Consignor messageConsignor, String messageTopic, String messageReck, String messageAck, String messageTargetReg, int messageLine)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.messageFrame.topic = messageTopic;
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

void ParseSOPositionMessage::parseJSONToStruct(JsonDocument doc, &SOPositionMessage object, DeserializationError error)
{   
    DBFUNCCALLln("ParseSOPositionMessage::parseJSONToStruct(JsonDocument doc, &SOPositionMessage object, DeserializationError error)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());
        object.packageId = "Parse failed";
    }
    else
    {
        object.line = doc["line"].as<int>;
    }
}

String ParseSOPositionMessage::parseStructToString(const SOPositionMessage *object)
{
    DBFUNCCALLln("ParseSOPositionMessage::parseStructToString(const SOPositionMessage *object)");
    String tempString = "{\"line\":\"" + object.line "\"}");
    return tempString;    
}

void ParseSOPositionMessage::setMessage(SOPositionMessage &object, unsigned int messageId, Consignor messageConsignor, String messageTopic, int messageLine)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.messageFrame.topic = messageTopic;
    object.line = messageLine;
}

// ParseSOStateMessage class
ParseSOStateMessage::ParseSOStateMessage()
{
}

ParseSOStateMessage::~ParseSOStateMessage()
{
}

void ParseSOStateMessage::parseJSONToStruct(JsonDocument doc, &SOStateMessage object, DeserializationError error)
{   
    DBFUNCCALLln("ParseSOStateMessage::parseJSONToStruct(JsonDocument doc, &SOStateMessage object, DeserializationError error)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());
        object.packageId = "Parse failed";
    }
    else
    {
        object.state = doc["state"].as<String>;
    }
}

String ParseSOStateMessage::parseStructToString(const SOStateMessage *object)
{
    DBFUNCCALLln("ParseSOStateMessage::parseStructToString(const SOStateMessage *object)");
    String tempString = "{\"state\":\"" + object.state "\"}");
    return tempString;    
}

void ParseSOStateMessage::setMessage(SOStateMessage &object, unsigned int messageId, Consignor messageConsignor, String messageTopic, String messageState)
{
    object.messageFrame.id = messageId;
    object.messageFrame.consignor = messageConsignor;
    object.messageFrame.topic = messageTopic;
    object.state = messageState;
}