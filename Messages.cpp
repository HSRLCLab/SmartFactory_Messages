/**
 * @file Messages.cpp
 * @author Philip Zellweger (philip.zellweger@hsr.ch)
 * @brief Serializing functions for the messagetypes
 * @version 0.1
 * @date 2019-11-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "Messages.h"

//======================BASECLASS=======================================================
//=======================================================================================
Message::Message()
{
}


Message::~Message()
{
}


std::shared_ptr<Message> Message::translateJsonToStruct(const char* payload, unsigned int length)
{
    DBFUNCCALLln("Message::translateJsonToStruct(const char*, unsigned int)");
    // Deserialize json object to json document
    DynamicJsonDocument tempJson(length);
    DeserializationError error = deserializeJson(tempJson, payload);
    
    // Generate pointer to return dynamic object
    std::shared_ptr<Message> retVal (nullptr);
   
    // switch to correct msgtype to activate polymorphism
    switch (tempJson["msgType"].as<unsigned int>())
    {
    case (unsigned int)MessageType::Package:
        {
            retVal = std::make_shared<PackageMessage>();
            retVal->parseJSONToStruct(tempJson, error);
            break;
        }
       
    case (unsigned int)MessageType::Error:
        {
            retVal = std::make_shared<ErrorMessage>();
            retVal->parseJSONToStruct(tempJson, error);
            break;
        }
    case (unsigned int)MessageType::SBAvailable:
        {
            retVal = std::make_shared<SBAvailableMessage>();
            retVal->parseJSONToStruct(tempJson, error);
            break;
        }
    case (unsigned int)MessageType::SBPosition:
        {
            retVal = std::make_shared<SBPositionMessage>();
            retVal->parseJSONToStruct(tempJson, error);
            break;
        }
    case (unsigned int)MessageType::SBState:
        {
            retVal = std::make_shared<SBStateMessage>();
            retVal->parseJSONToStruct(tempJson, error);
            break;
        }
    case (unsigned int)MessageType::SBToSVHandshake:
        {
            retVal = std::make_shared<SBToSVHandshakeMessage>();
            retVal->parseJSONToStruct(tempJson, error);
            break;
        }        
    case (unsigned int)MessageType::SVAvailable:
        {
            retVal = std::make_shared<SVAvailableMessage>();
            retVal->parseJSONToStruct(tempJson, error);
            break;
        }        
    case (unsigned int)MessageType::SVPosition:
        {
            retVal = std::make_shared<SVPositionMessage>();
            retVal->parseJSONToStruct(tempJson, error);
            break;
        }
    case (unsigned int)MessageType::SVState:
        {
            retVal = std::make_shared<SVStateMessage>();
            retVal->parseJSONToStruct(tempJson, error);
            break;
        }
    case (unsigned int)MessageType::SBToSOHandshake:
        {
            retVal = std::make_shared<SBToSOHandshakeMessage>();
            retVal->parseJSONToStruct(tempJson, error);
            break;
        }
    case (unsigned int)MessageType::SOPosition:
        {
            retVal = std::make_shared<SOPositionMessage>();
            retVal->parseJSONToStruct(tempJson, error);
            break;
        }
    case (unsigned int)MessageType::SOState:
        {
            retVal = std::make_shared<SOStateMessage>();
            retVal->parseJSONToStruct(tempJson, error);
            break;
        }
    case (unsigned int)MessageType::SOInit:
        {
            retVal = std::make_shared<SOInitMessage>();
            retVal->parseJSONToStruct(tempJson, error);
            break;
        }
    case (unsigned int)MessageType::SOBuffer:
        {
            retVal = std::make_shared<BufferMessage>();
            retVal->parseJSONToStruct(tempJson, error);
        }
    default:
        {   
        DBWARNING("Translation failed");
        break;
        }
    }
    return retVal;
}

String Message::translateStructToString(std::shared_ptr<Message> object)
{
    DBFUNCCALLln("Message::translateStructToString(std::shared_ptr<Message>)");
    String retVal = object->parseStructToString();
    return retVal;
}


//======================SPEZCLASS========================================================
//=======================================================================================


//======================PackageMessage===================================================
//=======================================================================================

PackageMessage::PackageMessage()
{
    DBFUNCCALLln("PackageMessage::PackageMessage()");
    this->msgType = MessageType::Package;
}

PackageMessage::~PackageMessage()
{
    DBFUNCCALLln("PackageMessage::~PackageMessage()");    
}

void PackageMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error) 
{
    
    DBFUNCCALLln("PackageMessage::parseJSONToStruct(JsonDocument, DeserializationError)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        this->msgId = 0;
    }
    else
    {
        DBINFO2ln("Parsed package message");
        // Parse message frame
        this->msgId = doc["msgId"].as<unsigned int>();
        this->msgType = (MessageType)(doc["msgType"].as<unsigned int>());
        this->msgLength = doc["msgLength"].as<unsigned int>();
        this->msgConsignor = (Consignor)(doc["msgConsignor"].as<unsigned int>());

        // Parse specific message
        this->packageId = doc["packageId"].as<unsigned int>();
        this->cargo = doc["cargo"].as<String>();
        this->targetDest = doc["targetDest"].as<String>();
        this->targetReg = doc["targetReg"].as<String>();
    }
    
}

String PackageMessage::parseStructToString()
{

    DBFUNCCALLln("PackageMessage::parseStructToString()");
    String tempString = "{\"msgId\":\"" + (String)this->msgId + "\",\"msgType\":\"" + (String)((unsigned int)(this->msgType)) + "\",\"msgLength\":\"" + (String)this->msgLength + "\",\"msgConsignor\":\"" + (String)((unsigned int)(this->msgConsignor)) + "\",\"packageId\":\"" + (String)this->packageId + "\",\"cargo\":\"" + this->cargo + "\",\"targetDest\":\"" + this->targetDest + "\",\"targetReg\":\"" + this->targetReg + "\"}";
    return tempString;
}


void PackageMessage::setMessage(unsigned int messageId, Consignor messageConsignor, unsigned int messagePackageId, String messageCargo, String messageTargetDest, String messageTargetReg)
{
    DBFUNCCALLln("PackageMessage::setMessage(unsigned int, Consignor, unsigned int, String, String, String)")
    this->msgId = messageId;
    this->msgConsignor = messageConsignor;
    this->packageId = messagePackageId;
    this->cargo = messageCargo;
    this->targetDest = messageTargetDest;
    this->targetReg = messageTargetReg;
    this->msgLength = sizeof(this);
}


//======================ErrorMessage=====================================================
//=======================================================================================

ErrorMessage::ErrorMessage()
{
    DBFUNCCALLln("ErrorMessage::ErrorMessage()");
    this->msgType = MessageType::Error;
}

ErrorMessage::~ErrorMessage()
{
    DBFUNCCALLln("ErrorMessage::~ErrorMessage()");
}

void ErrorMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("ErrorMessage::parseJSONToStruct(JsonDocument, DeserializationError)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        this->msgId = 0;
    }
    else
    {
        DBINFO2ln("Parsed error message");
        // Parse message frame
        this->msgId = doc["msgId"].as<unsigned int>();
        this->msgType = (MessageType)(doc["msgType"].as<unsigned int>());
        this->msgLength = doc["msgLength"].as<unsigned int>();
        this->msgConsignor = (Consignor)(doc["msgConsignor"].as<unsigned int>());

        // Parse specific message
        this->error = doc["error"].as<bool>();
        this->token = doc["token"].as<bool>();
    }    
}

String ErrorMessage::parseStructToString()
{
    DBFUNCCALLln("ErrorMessage::parseStructToString()");
    String tempString = "{\"msgId\":\"" + (String)this->msgId + "\",\"msgType\":\"" + (String)((unsigned int)(this->msgType)) + "\",\"msgLength\":\"" + (String)this->msgLength + "\",\"msgConsignor\":\"" + (String)((unsigned int)(this->msgConsignor)) + "\",\"error\":\"" + (String)this->error + "\",\"token\":\"" + (String)this->token + "\"}";
    return tempString;
}

void ErrorMessage::setMessage(unsigned int messageId, Consignor messageConsignor, bool messageError, bool messageToken)
{
    DBFUNCCALLln("ErrorMessage::setMessage(unsigned int, Consignor, bool, bool)");
    this->msgId = messageId;
    this->msgConsignor = messageConsignor;
    this->error = messageError;
    this->token = messageToken;
    this->msgLength = sizeof(this);
}

//======================SBAvailableMessage===============================================
//=======================================================================================

SBAvailableMessage::SBAvailableMessage()
{
    DBFUNCCALLln("SBAvailableMessage::SBAvailableMessage()");
    this->msgType = MessageType::SBAvailable;
}

SBAvailableMessage::~SBAvailableMessage()
{
    DBFUNCCALLln("SBAvailableMessage::~SBAvailableMessage()");
}

void SBAvailableMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("SBAvailableMessage::parseJSONToStruct(JsonDocument, DeserializationError)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        this->msgId = 0;
    }
    else
    {
        DBINFO2ln("Parsed smartbox available message");
        // Parse message frame
        this->msgId = doc["msgId"].as<unsigned int>();
        this->msgType = (MessageType)(doc["msgType"].as<unsigned int>());
        this->msgLength = doc["msgLength"].as<unsigned int>();
        this->msgConsignor = (Consignor)(doc["msgConsignor"].as<unsigned int>());

        // Parse specific message
        this->sector = doc["sector"].as<String>();
        this->line = doc["line"].as<int>();
        this->targetReg = doc["targetReg"].as<String>();
    }           
}

String SBAvailableMessage::parseStructToString()
{
    DBFUNCCALLln("SBAvailableMessage::parseStructToString()");
    String tempString = "{\"msgId\":\"" + (String)this->msgId + "\",\"msgType\":\"" + (String)((unsigned int)(this->msgType)) + "\",\"msgLength\":\"" + (String)this->msgLength + "\",\"msgConsignor\":\"" + (String)((unsigned int)(this->msgConsignor)) + "\",\"sector\":\"" + this->sector + "\",\"line\":\"" + (String)this->line + "\",\"targetReg\":\"" + this->targetReg + "\"}";
    return tempString;    
}

void SBAvailableMessage::setMessage(unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine, String messageTargetReg)
{
    DBFUNCCALLln("SBAvailableMessage::setMessage(unsigned int, Consignor, String, int, String)")
    this->msgId = messageId;
    this->msgConsignor = messageConsignor;
    this->sector = messageSector;
    this->line = messageLine;
    this->targetReg = messageTargetReg;
    this->msgLength = sizeof(this);
}

//======================SBPositionMessage================================================
//=======================================================================================
SBPositionMessage::SBPositionMessage()
{
    DBFUNCCALLln("SBPositionMessage::SBPositionMessage()");
    this->msgType = MessageType::SBPosition;
}

SBPositionMessage::~SBPositionMessage()
{
    DBFUNCCALLln("SBPositionMessage::~SBPositionMessage()");
}

void SBPositionMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("SBPositionMessage::parseJSONToStruct(JsonDocument, DeserializationError)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        this->msgId = 0;
    }
    else
    {
        DBINFO2ln("Parsed smartbox position message");
        // Parse message frame
        this->msgId = doc["msgId"].as<unsigned int>();
        this->msgType = (MessageType)(doc["msgType"].as<unsigned int>());
        this->msgLength = doc["msgLength"].as<unsigned int>();
        this->msgConsignor = (Consignor)(doc["msgConsignor"].as<unsigned int>());

        // Parse specific message
        this->sector = doc["sector"].as<String>();
        this->line = doc["line"].as<int>();
    }       
}

String SBPositionMessage::parseStructToString()
{
    DBFUNCCALLln("SBPositionMessage::parseStructToString()");
    String tempString = "{\"msgId\":\"" + (String)this->msgId + "\",\"msgType\":\"" + (String)((unsigned int)(this->msgType)) + "\",\"msgLength\":\"" + (String)this->msgLength + "\",\"msgConsignor\":\"" + (String)((unsigned int)(this->msgConsignor)) + "\",\"sector\":\"" + this->sector + "\",\"line\":\"" + (String)this->line + "\"}";
    return tempString;    
}

void SBPositionMessage::setMessage(unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine)
{
    DBFUNCCALLln("SBPositionMessage::setMessage(unsigned int, Consignor, String, int)");
    this->msgId = messageId;
    this->msgConsignor = messageConsignor;
    this->sector = messageSector;
    this->line = messageLine;
    this->msgLength = sizeof(this);
}


//======================SBStateMessage===================================================
//=======================================================================================

SBStateMessage::SBStateMessage()
{
    DBFUNCCALLln("SBStateMessage::SBStateMessage()");
    this->msgType = MessageType::SBState;
}

SBStateMessage::~SBStateMessage()
{
    DBFUNCCALLln("SBStateMessage::~SBStateMessage()");
}

void SBStateMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("SBStateMessage::parseJSONToStruct(JsonDocument, DeserializationError)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        this->msgId = 0;
    }
    else
    {
        DBINFO2ln("Parsed smartbox state message");
        // Parse message frame
        this->msgId = doc["msgId"].as<unsigned int>();
        this->msgType = (MessageType)(doc["msgType"].as<unsigned int>());
        this->msgLength = doc["msgLength"].as<unsigned int>();
        this->msgConsignor = (Consignor)(doc["msgConsignor"].as<unsigned int>());

        // Parse specific message
        this->state = doc["state"].as<String>();
    }   
}

String SBStateMessage::parseStructToString()
{
    DBFUNCCALLln("SBStateMessage::parseStructToString()");
    String tempString = "{\"msgId\":\"" + (String)this->msgId + "\",\"msgType\":\"" + (String)((unsigned int)(this->msgType)) + "\",\"msgLength\":\"" + (String)(this->msgLength) + "\",\"msgConsignor\":\"" + (String)((unsigned int)(this->msgConsignor)) + "\",\"state\":\"" + (this->state) +"\"}";
    return tempString;    
}

void SBStateMessage::setMessage(unsigned int messageId, Consignor messageConsignor, String messageState)
{
    DBFUNCCALLln("SBStateMessage::setMessage(unsigned int, Consignor, String)");
    this->msgId = messageId;
    this->msgConsignor = messageConsignor;
    this->state = messageState;
    this->msgLength = (unsigned int)sizeof(this);
}

//======================SBToSVHandshakeMessage===========================================
//=======================================================================================

SBToSVHandshakeMessage::SBToSVHandshakeMessage()
{
    DBFUNCCALLln("SBToSVHandshakeMessage::SBToSVHandshakeMessage()");
    this->msgType = MessageType::SBToSVHandshake;
}

SBToSVHandshakeMessage::~SBToSVHandshakeMessage()
{
    DBFUNCCALLln("SBToSVHandshakeMessage::~SBToSVHandshakeMessage()");
}


void SBToSVHandshakeMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("SBToSVHandshakeMessage::parseJSONToStruct(JsonDocument, DeserializationError)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        this->msgId = 0;
    }
    else
    {
        DBINFO2ln("Parsed smartbox to smartvehicle handshake message");
        // Parse message frame
        this->msgId = doc["msgId"].as<unsigned int>();
        this->msgType = (MessageType)(doc["msgType"].as<unsigned int>());
        this->msgLength = doc["msgLength"].as<unsigned int>();
        this->msgConsignor = (Consignor)(doc["msgConsignor"].as<unsigned int>());

        // Parse specific message
        this->reck = doc["reck"].as<String>();
        this->ack = doc["ack"].as<String>();
        this->cargo = doc["cargo"].as<String>();
        this->line = doc["line"].as<int>();
    }       
}


String SBToSVHandshakeMessage::parseStructToString()
{
    DBFUNCCALLln("SBToSVHandshakeMessage::parseStructToString()");
    String tempString = "{\"msgId\":\"" + (String)this->msgId + "\",\"msgType\":\"" + (String)((unsigned int)(this->msgType)) + "\",\"msgLength\":\"" + (String)this->msgLength + "\",\"msgConsignor\":\"" + (String)((unsigned int)(this->msgConsignor)) + "\",\"reck\":\"" + this->reck + "\",\"ack\":\"" + this->ack + "\",\"cargo\":\"" + this->cargo + "\",\"line\":\"" + (String)this->line + "\"}";
    return tempString;    
}

void SBToSVHandshakeMessage::setMessage(unsigned int messageId, Consignor messageConsignor, String messageReck, String messageAck, String messageCargo, int messageLine)
{
    DBFUNCCALLln("SBToSVHandshakeMessage::setMessage(unsigned int, Consignor, String, String, String, int)");
    this->msgId = messageId;
    this->msgConsignor = messageConsignor;
    this->reck = messageReck;
    this->ack = messageAck;
    this->cargo = messageCargo;
    this->line = messageLine;
    this->msgLength = sizeof(this);
}

//======================SVAvailableMessage===============================================
//=======================================================================================

SVAvailableMessage::SVAvailableMessage()
{
    DBFUNCCALLln("SVAvailableMessage::SVAvailableMessage()");
    this->msgType = MessageType::SVAvailable;
}

SVAvailableMessage::~SVAvailableMessage()
{
    DBFUNCCALLln("SVAvailableMessage::~SVAvailableMessage()");
}

void SVAvailableMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("SVAvailableMessage::parseJSONToStruct(JsonDocument, DeserializationError)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        this->msgId = 0;
    }
    else
    {
        DBINFO2ln("Parsed smartvehicle available message");
        // Parse message frame
        this->msgId = doc["msgId"].as<unsigned int>();
        this->msgType = (MessageType)(doc["msgType"].as<unsigned int>());
        this->msgLength = doc["msgLength"].as<unsigned int>();
        this->msgConsignor = (Consignor)(doc["msgConsignor"].as<unsigned int>());

        // Parse specific message
        this->sector = doc["sector"].as<String>();
        this->line = doc["line"].as<int>();
    }       
}

String SVAvailableMessage::parseStructToString()
{
    DBFUNCCALLln("SVAvailableMessage::parseStructToString()");
    String tempString = "{\"msgId\":\"" + (String)this->msgId + "\",\"msgType\":\"" + (String)((unsigned int)(this->msgType)) + "\",\"msgLength\":\"" + (String)this->msgLength + "\",\"msgConsignor\":\"" + (String)((unsigned int)(this->msgConsignor)) + "\",\"sector\":\"" + this->sector + "\",\"line\":\"" + (String)this->line + "\"}";
    return tempString;    
}

void SVAvailableMessage::setMessage(unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine)
{
    DBFUNCCALLln("SVAvailableMessage::setMessage(unsigned int, Consignor, String, int)");
    this->msgId = messageId;
    this->msgConsignor = messageConsignor;
    this->sector = messageSector;
    this->line = messageLine;
    this->msgLength = sizeof(this);
}

//======================SVPositionMessage================================================
//=======================================================================================

SVPositionMessage::SVPositionMessage()
{
    DBFUNCCALLln("SVPositionMessage::SVPositionMessage()");
    this->msgType = MessageType::SVPosition;
}

SVPositionMessage::~SVPositionMessage()
{
    DBFUNCCALLln("SVPositionMessage::~SVPositionMessage()");
}

void SVPositionMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("SVPositionMessage::parseJSONToStruct(JsonDocument, DeserializationError)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        this->msgId = 0;
    }
    else
    {
        DBINFO2ln("Parsed smartvehicle position message");
        // Parse message frame
        this->msgId = doc["msgId"].as<unsigned int>();
        this->msgType = (MessageType)(doc["msgType"].as<unsigned int>());
        this->msgLength = doc["msgLength"].as<unsigned int>();
        this->msgConsignor = (Consignor)(doc["msgConsignor"].as<unsigned int>());

        // Parse specific message
        this->sector = doc["sector"].as<String>();
        this->line = doc["line"].as<int>();
    }
}

String SVPositionMessage::parseStructToString()
{
    DBFUNCCALLln("SVPositionMessage::parseStructToString()");
    String tempString = "{\"msgId\":\"" + (String)this->msgId + "\",\"msgType\":\"" + (String)((unsigned int)(this->msgType)) + "\",\"msgLength\":\"" + (String)this->msgLength + "\",\"msgConsignor\":\"" + (String)((unsigned int)(this->msgConsignor)) + "\",\"sector\":\"" + this->sector + "\",\"line\":\"" + (String)this->line + "\"}";
    return tempString;    
}

void SVPositionMessage::setMessage(unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine)
{
    DBFUNCCALLln("SVPositionMessage::setMessage(unsigned int, Consignor, String, int)");
    this->msgId = messageId;
    this->msgConsignor = messageConsignor;
    this->sector = messageSector;
    this->line = messageLine;
    this->msgLength = sizeof(this);
}

//======================SVStateMessage===================================================
//=======================================================================================

SVStateMessage::SVStateMessage()
{
    DBFUNCCALLln("SVStateMessage::SVStateMessage()");
    this->msgType = MessageType::SVState;
}

SVStateMessage::~SVStateMessage()
{
    DBFUNCCALLln("SVStateMessage::~SVStateMessage()");
}

void SVStateMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{   
    DBFUNCCALLln("SVStateMessage::parseJSONToStruct(JsonDocument, DeserializationError)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        this->msgId = 0;
    }
    else
    {
        DBINFO2ln("Parsed smartvehicle state message");
        // Parse message frame
        this->msgId = doc["msgId"].as<unsigned int>();
        this->msgType = (MessageType)(doc["msgType"].as<unsigned int>());
        this->msgLength = doc["msgLength"].as<unsigned int>();
        this->msgConsignor = (Consignor)(doc["msgConsignor"].as<unsigned int>());

        // Parse specific message
        this->state = doc["state"].as<String>();
    }
}

String SVStateMessage::parseStructToString()
{
    DBFUNCCALLln("SVStateMessage::parseStructToString()");
    String tempString = "{\"msgId\":\"" + (String)this->msgId + "\",\"msgType\":\"" + (String)((unsigned int)(this->msgType)) + "\",\"msgLength\":\"" + (String)this->msgLength + "\",\"msgConsignor\":\"" + (String)((unsigned int)(this->msgConsignor)) + "\",\"state\":\"" + this->state + "\"}";
    return tempString;    
}

void SVStateMessage::setMessage(unsigned int messageId, Consignor messageConsignor, String messageState)
{
    DBFUNCCALLln("SVStateMessage::setMessage(unsigned int, Consignor, String)");
    this->msgId = messageId;
    this->msgConsignor = messageConsignor;
    this->state = messageState;
    this->msgLength = sizeof(this);
}


//======================SBToSOHandshakeMessage===========================================
//=======================================================================================

SBToSOHandshakeMessage::SBToSOHandshakeMessage()
{
    DBFUNCCALLln("SBToSOHandshakeMessage::SBToSOHandshakeMessage()");
    this->msgType = MessageType::SBToSOHandshake;
}

SBToSOHandshakeMessage::~SBToSOHandshakeMessage()
{
    DBFUNCCALLln("SBToSOHandshakeMessage::~SBToSOHandshakeMessage()");
}

void SBToSOHandshakeMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{   
    DBFUNCCALLln("SBToSOHandshakeMessage::parseJSONToStruct(JsonDocument, DeserializationError)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        this->msgId = 0;
    }
    else
    {
        DBINFO2ln("Parsed smartbox to sortic handshake message");
        // Parse message frame
        this->msgId = doc["msgId"].as<unsigned int>();
        this->msgType = (MessageType)(doc["msgType"].as<unsigned int>());
        this->msgLength = doc["msgLength"].as<unsigned int>();
        this->msgConsignor = (Consignor)(doc["msgConsignor"].as<unsigned int>());

        // Parse specific message
        this->req = doc["req"].as<String>();
        this->ack = doc["ack"].as<String>();
        this->cargo = doc["cargo"].as<String>();
        this->targetReg = doc["targetReg"].as<String>();
        this->line = doc["line"].as<int>();
    }
}

String SBToSOHandshakeMessage::parseStructToString()
{
    DBFUNCCALLln("SBToSOHandshakeMessage::parseStructToString()");
    String tempString = "{\"msgId\":\"" + (String)this->msgId + "\",\"msgType\":\"" + (String)((unsigned int)(this->msgType)) + "\",\"msgLength\":\"" + (String)this->msgLength + "\",\"msgConsignor\":\"" + (String)((unsigned int)(this->msgConsignor)) + "\",\"reck\":\"" + this->req + "\",\"ack\":\"" + this->ack + "\",\"cargo\":\"" + this->cargo + "\",\"targetReg\":\"" + this->targetReg + "\",\"line\":\"" + (String)this->line + "\"}";
    return tempString;    
}

void SBToSOHandshakeMessage::setMessage(unsigned int messageId, Consignor messageConsignor, String messageReq, String messageAck, String messageCargo, String messageTargetReg, int messageLine)
{
    DBFUNCCALLln("SBToSOHandshakeMessage::setMessage(unsigned int, Consignor, String, String, String, String, int)");
    this->msgId = messageId;
    this->msgConsignor = messageConsignor;
    this->req = messageReq;
    this->ack = messageAck;
    this->cargo = messageCargo;
    this->targetReg = messageTargetReg;
    this->line = messageLine;
    this->msgLength = sizeof(this);
}

//======================SOPositionMessage================================================
//=======================================================================================

SOPositionMessage::SOPositionMessage()
{
    DBFUNCCALLln("SOPositionMessage::SOPositionMessage()");
    this->msgType = MessageType::SOPosition;
}

SOPositionMessage::~SOPositionMessage()
{
    DBFUNCCALLln("SOPositionMessage::~SOPositionMessage()");
}


void SOPositionMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{   
    DBFUNCCALLln("SOPositionMessage::parseJSONToStruct(JsonDocument, DeserializationError)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        this->msgId = 0;
    }
    else
    {
        DBINFO2ln("Parsed sortic position message");
        // Parse message frame
        this->msgId = doc["msgId"].as<unsigned int>();
        this->msgType = (MessageType)(doc["msgType"].as<unsigned int>());
        this->msgLength = doc["msgLength"].as<unsigned int>();
        this->msgConsignor = (Consignor)(doc["msgConsignor"].as<unsigned int>());

        // Parse specific message
        this->line = doc["line"].as<int>();
    }
}

String SOPositionMessage::parseStructToString()
{
    DBFUNCCALLln("SOPositionMessage::parseStructToString()");
    String tempString = "{\"msgId\":\"" + (String)this->msgId + "\",\"msgType\":\"" + (String)((unsigned int)(this->msgType)) + "\",\"msgLength\":\"" + (String)this->msgLength + "\",\"msgConsignor\":\"" + (String)((unsigned int)(this->msgConsignor)) + "\",\"line\":\"" + (String)this->line + "\"}";
    return tempString;    
}

void SOPositionMessage::setMessage(unsigned int messageId, Consignor messageConsignor, int messageLine)
{
    DBFUNCCALLln("SOPositionMessage::setMessage(unsigned int, Consignor, int)");
    this->msgId = messageId;
    this->msgConsignor = messageConsignor;
    this->line = messageLine;
    this->msgLength = sizeof(this);
}

//======================SOStateMessage===================================================
//=======================================================================================

SOStateMessage::SOStateMessage()
{
    DBFUNCCALLln("SOStateMessage::SOStateMessage()");
    this->msgType = MessageType::SOState;
}

SOStateMessage::~SOStateMessage()
{
    DBFUNCCALLln("SOStateMessage::~SOStateMessage()");
}

void SOStateMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{   
    DBFUNCCALLln("SOStateMessage::parseJSONToStruct(JsonDocument, DeserializationError)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        this->msgId = 0;
    }
    else
    {
        DBINFO2ln("Parsed sortic state message");
        // Parse message frame
        this->msgId = doc["msgId"].as<unsigned int>();
        this->msgType = (MessageType)(doc["msgType"].as<unsigned int>());
        this->msgLength = doc["msgLength"].as<unsigned int>();
        this->msgConsignor = (Consignor)(doc["msgConsignor"].as<unsigned int>());

        // Parse specific message
        this->state = doc["state"].as<String>();
    }
}

String SOStateMessage::parseStructToString()
{
    DBFUNCCALLln("SOStateMessage::parseStructToString()");
    String tempString = "{\"msgId\":\"" + (String)this->msgId + "\",\"msgType\":\"" + (String)((unsigned int)(this->msgType)) + "\",\"msgLength\":\"" + (String)this->msgLength + "\",\"msgConsignor\":\"" + (String)((unsigned int)(this->msgConsignor)) + "\",\"state\":\"" + this->state + "\"}";
    return tempString;    
}

void SOStateMessage::setMessage(unsigned int messageId, Consignor messageConsignor, String messageState)
{
    DBFUNCCALLln("SOStateMessage::setMessage(unsigned int, Consignor, String)");
    this->msgId = messageId;
    this->msgConsignor = messageConsignor;
    this->state = messageState;
    this->msgLength = sizeof(this);
}

//======================SOInitMessage====================================================
//=======================================================================================

SOInitMessage::SOInitMessage()
{
    DBFUNCCALLln("SOInitMessage::SOInitMessage()");
    this->msgType = MessageType::SOInit;
}

SOInitMessage::~SOInitMessage()
{
    DBFUNCCALLln("SOInitMessage::~SOInitMessage()");
}

void SOInitMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{   
    DBFUNCCALLln("SOInitMessage::parseJSONToStruct(JsonDocument, DeserializationError)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        this->msgId = 0;
    }
    else
    {
        DBINFO2ln("Parsed sortic init message");
        // Parse message frame
        this->msgId = doc["msgId"].as<unsigned int>();
        this->msgType = (MessageType)(doc["msgType"].as<unsigned int>());
        this->msgLength = doc["msgLength"].as<unsigned int>();
        this->msgConsignor = (Consignor)(doc["msgConsignor"].as<unsigned int>());

        // Parse specific message
        this->state = doc["state"].as<String>();
        this->req = doc["req"].as<String>();
        this->ack = doc["ack"].as<String>();
        this->cargo = doc["cargo"].as<String>();
        this->targetReg = doc["targetReg"].as<String>();
        this->line = doc["line"].as<int>();
        this->packageId = doc["packageId"].as<unsigned int>();
        this->targetDest = doc["targetDest"].as<String>();
        this->error = doc["error"].as<bool>();
        this->token = doc["token"].as<bool>();
    }
}

String SOInitMessage::parseStructToString()
{
    DBFUNCCALLln("SOInitMessage::parseStructToString()");
    String tempString = "{\"msgId\":\"" + (String)this->msgId + "\",\"msgType\":\"" + (String)((unsigned int)(this->msgType)) + "\",\"msgLength\":\"" + (String)this->msgLength + "\",\"msgConsignor\":\"" + (String)((unsigned int)(this->msgConsignor)) + "\",\"state\":\"" + this->state + "\",\"reck\":\"" + this->req + "\",\"ack\":\"" + this->ack + "\",\"cargo\":\"" + this->cargo + "\",\"targetReg\":\"" + this->targetReg + "\",\"line\":\"" + (String)this->line + "\",\"targetReg\":\"" + this->targetReg + "\",\"error\":\"" + (String)this->error + "\",\"token\":\"" + (String)this->token + "\"}";
    return tempString;    
}

void SOInitMessage::setMessage()
{
    DBFUNCCALLln("SOInitMessage::setMessage()");
    this->msgId = 0;
    this->msgConsignor = Consignor::SO1;
    this->state = "null";
    this->req = "null";
    this->ack = "null";
    this->cargo = "null";
    this->targetReg = "null";
    this->line = -1;
    this->packageId = 0;
    this->targetDest = "null";
    this->error = false;
    this->token = false;
    this->msgLength = sizeof(this);
}

//======================BufferMessage===================================================
//=======================================================================================

BufferMessage::BufferMessage()
{
    DBFUNCCALLln("BufferMessage::BufferMessage()");
    this->msgType = MessageType::Error;
}

BufferMessage::~BufferMessage()
{
    DBFUNCCALLln("BufferMessage::~BufferMessage()");
}

void BufferMessage::parseJSONToStruct(JsonDocument doc, DeserializationError error)
{
    DBFUNCCALLln("BufferMessage::parseJSONToStruct(JsonDocument, DeserializationError)");
    if (error)
    {
        DBWARNING("deserializeJson() failed: ");
        DBWARNINGln(error.c_str());

        // set msgId to zero, zero means errorId
        this->msgId = 0;
    }
    else
    {
        DBINFO2ln("Parsed buffer message");
        // Parse message frame
        this->msgId = doc["msgId"].as<unsigned int>();
        this->msgType = (MessageType)(doc["msgType"].as<unsigned int>());
        this->msgLength = doc["msgLength"].as<unsigned int>();
        this->msgConsignor = (Consignor)(doc["msgConsignor"].as<unsigned int>());

        // Parse specific message
        this->full = doc["full"].as<bool>();
        this->cleared = doc["cleared"].as<bool>();
    }    
}

String BufferMessage::parseStructToString()
{
    DBFUNCCALLln("BufferMessage::parseStructToString()");
    String tempString = "{\"msgId\":\"" + (String)this->msgId + "\",\"msgType\":\"" + (String)((unsigned int)(this->msgType)) + "\",\"msgLength\":\"" + (String)this->msgLength + "\",\"msgConsignor\":\"" + (String)((unsigned int)(this->msgConsignor)) + "\",\"full\":\"" + (String)this->full + "\",\"cleared\":\"" + (String)this->cleared + "\"}";
    return tempString;
}

void BufferMessage::setMessage(unsigned int messageId, Consignor messageConsignor, bool messageFull, bool messageCleared)
{
    DBFUNCCALLln("BufferMessage::setMessage(unsigned int, Consignor, bool, bool)");
    this->msgId = messageId;
    this->msgConsignor = messageConsignor;
    this->full = messageFull;
    this->cleared = messageCleared;
    this->msgLength = sizeof(this);
}