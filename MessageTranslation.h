/**
 * @file MessageTranslation.h
 * @author Philip Zellweger (philip.zellweger@hsr.ch)
 * @brief Serializing functions for the messagetypes
 * @version 0.1
 * @date 2019-11-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef MESSAGETRANSLATION_H__
#define MESSAGETRANSLATION_H__

#include <Arduino.h>
#include <ArduinoJson.h>
#include "LogConfiguration.h"
#include "Message.h"


// GLOBAL defined translatefunction

/**
 * @brief Static function to serialize a JSON object to a message struct
 * 
 * @param payload - byte*
 * @param length - unsigned int
 */
static void *translateJsonToStruct(byte* payload, unsigned int length);

/**
 * @brief Static template function to serialize a message struct to a publish string
 * 
 * @tparam T - typename
 * @param object - const &typename
 * @return String 
 */
template<typename T>
static String translateStructToString(const &T object);



#if defined(BOX)  || defined(SORTIC) || defined(VEHICLE)
/**
 * @brief Parent message class with virtual functions to overwrite in child class
 * 
 */
class Message
{
    private:
    public:
    /**
     * @brief Construct a new Message object
     * 
     */
    Message();

    /**
     * @brief Destroy the Message object
     * 
     */
    ~Message();

    /**
     * @brief Virtual function to parse JSON object to a message struct
     * 
     * @param doc - JsonDocument
     * @param error - DeserializationError
     * @return void* 
     */
    virtual static void *parseJSONToStruct(JsonDocument doc, DeserializationError error);   

    /**
     * @brief Virtual function parse message struct to publish string
     * 
     * @param messageClass - this
     * @return String 
     */
    virtual static String parseStructToString(this messageClass);

    /**
     * @brief Set the Message object
     * 
     */
    virtual static void setMessage();
};

/**
 * @brief Child class to serialize package message
 * 
 */
class ParsePackageMessage : Message
{
private:    
public:

    /**
     * @brief Construct a new Parse Package Message object
     * 
     */
    ParsePackageMessage();

    /**
     * @brief Destroy the Parse Package Message object
     * 
     */
    ~ParsePackageMessage();

    /**
     * @brief Translate package message JSON to struct
     * 
     * @param doc - JsonDocument
     * @param error - DeserializationError
     * @return PackageMessage*
     */
    virtual static PackageMessage* parseJSONToStruct(JsonDocument doc, DeserializationError error);

    /**
     * @brief Translate package message struct to publish string
     * 
     * @param messageClass - PackageMessage
     * @return String 
     */
    virtual static String parseStructToString(PackageMessage messageClass);

    /**
     * @brief Set the Message object package
     * 
     * @param object - &PackageMessage
     * @param messageId - unsigned int
     * @param messageConsignor - Consignor
     * @param messagePackageId - String
     * @param messageCargo - String
     * @param messageTargetDest - String
     * @param messageTargetReg - String
     */
    virtual static void setMessage(PackageMessage &object, unsigned int messageId, Consignor messageConsignor, String messagePackageId, String messageCargo, String messageTargetDest, String messageTargetReg);
};

/**
 * @brief Child class to serialize error message
 * 
 */
class ParseErrorMessage : Message
{

private:
public:

    /**
     * @brief Construct a new Parse Error Message object
     * 
     */
    ParseErrorMessage();

    /**
     * @brief Destroy the Parse Error Message object
     * 
     */
    ~ParseErrorMessage();

    /**
     * @brief Translate error message JSON to struct
     * 
     * @param doc - JsonDocument
     * @param error - DeserializationError
     * @return ErrorMessage*
     */
    virtual static ErrorMessage *parseJSONToStruct(JsonDocument doc, DeserializationError error);

    /**
     * @brief Translate error message struct to string 
     * 
     * @param messageClass - ErrorMessage
     * @return String 
     */
    virtual static String parseStructToString(ErrorMessage messageClass);

    /**
     * @brief Set the Message object
     * 
     * @param object - &ErrorMessage
     * @param messageId - unsigned int
     * @param messageConsignor - Consignor
     * @param messageError - bool
     * @param messageToken - bool
     */
    virtual static void setMessage(ErrorMessage &object, unsigned int messageId, Consignor messageConsignor, bool messageError, bool messageToken);
};

/**
 * @brief Child class to serialize smartbox available message
 * 
 */
class ParseSBAvailableMessage : Message
{
private:
public:

    /**
     * @brief Construct a new Parse SB Available Message object
     * 
     */
    ParseSBAvailableMessage();

    /**
     * @brief Destroy the My JSON Message SB Available object
     * 
     */
    ~MyJSONMessageSBAvailable();

    /**
     * @brief Translate smartbox available message json to struct
     * 
     * @param doc - JsonDocument
     * @param error - DeserializationError
     * @return SBAvailableMessage*
     */
    virtual static SBAvailableMessage *parseJSONToStruct(JsonDocument doc, DeserializationError error);

    /**
     * @brief Translate smartbox available message struct to string
     * 
     * @param messageClass - SBAvailableMessage
     * @return String 
     */
    virtual static String parseStructToString(SBAvailableMessage messageClass);

    /**
     * @brief Set the Message object smartbox available message
     * 
     * @param object - &SBAvailableMessage
     * @param messageId - unsigned int
     * @param messageConsignor - Consignor
     * @param messageSector - String
     * @param messageLine - int
     * @param messageTargetReg - String
     */
    virtual static void setMessage(SBAvailableMessage &object, unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine, String messageTargetReg);
};

/**
 * @brief Child class to serialize smartbox possition message
 * 
 */
class ParseSBPositionMessage : Message
{
private:
public:

    /**
     * @brief Construct a new Parse S B Position Message object
     * 
     */
    ParseSBPositionMessage();

    /**
     * @brief Destroy the Parse SB Position Message object
     * 
     */
    ~ParseSBPositionMessage();

    /**
     * @brief Translate smartbox position message json to struct
     * 
     * @param doc - JsonDocument
     * @param error - DeserializationError
     * @return SBPositionMessage*
     */
    virtual static SBPositionMessage *parseJSONToStruct(JsonDocument doc, DeserializationError error);

    /**
     * @brief Translate smartbox position message struct to publish string
     * 
     * @param messageClass - SBPositionMessage
     * @return String 
     */
    virtual static String parseStructToString(SBPositionMessage messageClass);

    /**
     * @brief Set the Message object smartbox position
     * 
     * @param object - SBPositionMessage
     * @param messageId - unsigned int
     * @param messageConsignor - Consignor
     * @param messageSector - string
     * @param messageLine - int
     */
    virtual static void setMessage(SBPositionMessage &object, unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine);
};

/**
 * @brief Class to serialize smartbox state message
 * 
 */
class ParseSBStateMessage : Message
{
private:
public:

    /**
     * @brief Construct a new Parse S B State Message object
     * 
     */
    ParseSBStateMessage();

    /**
     * @brief Destroy the Parse S B State Message object
     * 
     */
    ~ParseSBStateMessage();

    /**
     * @brief Translate smartbox state message json to struct
     * 
     * @param doc - JsonDocument
     * @param error - DeserializationError
     * @return SBStateMessage*
     */
    virtual static SBStateMessage *parseJSONToStruct(JsonDocument doc, DeserializationError error);

    /**
     * @brief Translate smartbox state message struct to string
     * 
     * @param messageClass - SBStateMessage
     * @return String 
     */
    virtual static String parseStructToString(SBStateMessage messageClass);

    /**
     * @brief Set the Message object smartbox state
     * 
     * @param object - SBStateMessage
     * @param messageId - unsigned int
     * @param messageConsignor - Consignor
     * @param messageState - String
     */
    virtual static void setMessage(SBStateMessage &object, unsigned int messageId, Consignor messageConsignor, String messageState);
};

#if defined(BOX) || defined(VEHICLE)

/**
 * @brief Class to serialize smartbox to smartvehicle handshake message
 * 
 */
class ParseSBtoSVHandshakeMessage : Message
{
private:   
public:

    /**
     * @brief Construct a new Parse SB to SV Handshake Message object
     * 
     */
    ParseSBtoSVHandshakeMessage();

    /**
     * @brief Destroy the Parse SB to SV Handshake Message object
     * 
     */
    ~ParseSBtoSVHandshakeMessage();

    /**
     * @brief Translate smartbox to smartvehicle handshake message json to struct
     * 
     * @param doc - JsonDocument
     * @param error - DeserializationError
     * @return SBToSVHandshakeMessage*
     */
    virtual static SBToSVHandshakeMessage *parseJSONToStruct(JsonDocument doc, DeserializationError error);

    /**
     * @brief Translate smartbox to smartvehicle handshake message struct to publish string
     * 
     * @param messageClass - SBToSVHandshakeMessage
     * @return String 
     */
    virtual static String parseStructToString(SBToSVHandshakeMessage messageClass);

    /**
     * @brief Set the Message object smartbox to smartvehicle handshake 
     * 
     * @param object - SBToSVHandshakeMessage
     * @param messageId - unsigned int
     * @param messageConsignor - Consignor
     * @param messageReck - String
     * @param messageAck - String
     * @param messageCargo - String
     * @param messageLine - int
     */
    virtual static void setMessage(SBToSVHandshakeMessage &object, unsigned int messageId, Consignor messageConsignor, String messageReck, String messageAck, String messageCargo, int messageLine);
};


/**
 * @brief Class to serialize smartvehicle available message
 * 
 */
class ParseSVAvailableMessage : Message
{
private:
public:

    /**
     * @brief Construct a new Parse SV Available Message object
     * 
     */
    ParseSVAvailableMessage();

    /**
     * @brief Destroy the Parse SV Available Message object
     * 
     */
    ~ParseSVAvailableMessage();

    /**
     * @brief Translate smartvehicle available message json to struct
     * 
     * @param doc - JsonDocument
     * @param error - DeserializationError
     * @return SVAvailableMessage*
     */
    virtual static SVAvailableMessage *parseJSONToStruct(JsonDocument doc, DeserializationError error);

    /**
     * @brief Translate smartvehicle available message struct to publish string
     * 
     * @param messageClass - SVAvailableMessage
     * @return String 
     */
    virtual static String parseStructToString(SVAvailableMessage messageClass);

    /**
     * @brief Set the Message object smartvehicle available
     * 
     * @param object - &SVAvailableMessage
     * @param messageId - unsigned int
     * @param messageConsignor - Consignor
     * @param messageSector - String
     * @param messageLine - int
     */
    virtual static void setMessage(SVAvailableMessage &object, unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine);
};

/**
 * @brief Class to serialize smartvehicle position message
 * 
 */
class ParseSVPositionMessage : Message
{
private:
public:

    /**
     * @brief Construct a new Parse SV Position Message object
     * 
     */
    ParseSVPositionMessage();

    /**
     * @brief Destroy the Parse SV Position Message object
     * 
     */
    ~ParseSVPositionMessage();

    /**
     * @brief Translate smartvehicle position message json to struct
     * 
     * @param doc - JsonDocument
     * @param error - DeserializationError
     * @return SVPositionMessage*
     */
    virtual static SVPositionMessage *parseJSONToStruct(JsonDocument doc, DeserializationError error);

    /**
     * @brief Translate smartvehicle position message struct to publish string
     * 
     * @param messageClass - SVPositionMessage
     * @return String 
     */
    virtual static String parseStructToString(SVPositionMessage messageClass);

    /**
     * @brief Set the Message object smartvehicle position
     * 
     * @param object - SVPositionMessage
     * @param messageId - unsigned int
     * @param messageConsignor - Consignor
     * @param messageSector - String
     * @param messageLine - int
     */
    virtual static void setMessage(SVPositionMessage &object, unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine);
};

/**
 * @brief Class to serialize smartvehicle state message
 * 
 */
class ParseSVStateMessage : Message
{
private:
public:

    /**
     * @brief Construct a new Parse SV State Message object
     * 
     */
    ParseSVStateMessage();

    /**
     * @brief Destroy the Parse SV State Message object
     * 
     */
    ~ParseSVStateMessage();

    /**
     * @brief Translate smartvehicle state message json to struct
     * 
     * @param doc - JsonDocument
     * @param error - DeserializationError
     * @return SVStateMessage*
     */
    virtual static SVStateMessage *parseJSONToStruct(JsonDocument doc, DeserializationError error);

    /**
     * @brief Translate smartvehicle state message struct to publish string
     * 
     * @param messageClass . SVStateMessage
     * @return String 
     */
    virtual static String parseStructToString(SVStateMessage messageClass);

    /**
     * @brief Set the Message object smartvehicle state 
     * 
     * @param object - SVStateMessage
     * @param messageId - unsigned int
     * @param messageConsignor - Consignor
     * @param messageState - String
     */
    virtual static void setMessage(SVStateMessage &object, unsigned int messageId, Consignor messageConsignor, String messageState);
};

#if defined(BOX) || defined(SORTIC)

/**
 * @brief Class to serialize smartbox to sortic handshake message
 * 
 */
class ParseSBtoSOHandshakeMessage : Message
{
private:
public:

    /**
     * @brief Construct a new Parse SB to SO Handshake Message object
     * 
     */
    ParseSBtoSOHandshakeMessage();

    /**
     * @brief Destroy the Parse SB to SO Handshake Message object
     * 
     */
    ~ParseSBtoSOHandshakeMessage();

    /**
     * @brief Translate smartbox to sortic handshake message json to struct
     * 
     * @param doc - JsonDocument
     * @param error - DeserializationError
     * @return SBtoSOHandshakeMessage*
     */
    virtual static SBtoSOHandshakeMessage *parseJSONToStruct(JsonDocument doc, DeserializationError error);

    /**
     * @brief Translate smartbox to sortic handshake message struct to publish message
     * 
     * @param messageClass - SBtoSOHandshakeMessage
     * @return String 
     */
    virtual static String parseStructToString(SBtoSOHandshakeMessage messageClass);

    /**
     * @brief Set the Message object smartbox to sortic handshake 
     * 
     * @param object - SBtoSOHandshakeMessage
     * @param messageId - unsigned int
     * @param messageConsignor - Consignor
     * @param messageReck - String
     * @param messageAck - String
     * @param messageTargetReg - String
     * @param messageLine - int
     */
    virtual static void setMessage(SBtoSOHandshakeMessage &object, unsigned int messageId, Consignor messageConsignor, String messageReck = "-1", String messageAck = "-1", String messageTargetReg = "-1", int messageLine = -1);
};

/**
 * @brief Class to serialize sortic position message
 * 
 */
class ParseSOPositionMessage : Message
{
private:
public:

    /**
     * @brief Construct a new Parse SO Position Message object
     * 
     */
    ParseSOPositionMessage();

    /**
     * @brief Destroy the Parse SO Position Message object
     * 
     */
    ~ParseSOPositionMessage();

    /**
     * @brief Translate sortic position message json to struct
     * 
     * @param doc - JsonDocument
     * @param error - DeserializationError
     * @return SOPositionMessage*
     */
    virtual static SOPositionMessage *parseJSONToStruct(JsonDocument doc, DeserializationError error);

    /**
     * @brief Translate sortic position message struct to publish string
     * 
     * @param messageClass 
     * @return String 
     */
    virtual static String parseStructToString(SOPositionMessage messageClass);

    /**
     * @brief Set the Message object sortic position
     * 
     * @param object - &SOPositionMessage
     * @param messageId - unsigned int
     * @param messageConsignor - Consignor
     * @param messageLine - int
     */
    virtual static void setMessage(SOPositionMessage &object, unsigned int messageId, Consignor messageConsignor, int messageLine);
};

/**
 * @brief Class to serialize sortic state message
 * 
 */
class ParseSOStateMessage : Message
{
private:
public:

    /**
     * @brief Construct a new Parse SO State Message object
     * 
     */
    ParseSOStateMessage();

    /**
     * @brief Destroy the Parse SO State Message object
     * 
     */
    ~ParseSOStateMessage();

    /**
     * @brief Translate sortic state message json to struct
     * 
     * @param doc - JsonDocument
     * @param error - DeserializationError
     * @return SOStateMessage*
     */
    virtual static SOStateMessage *parseJSONToStruct(JsonDocument doc, DeserializationError error);

    /**
     * @brief Translate sortic state message struct to publish state
     * 
     * @param messageClass - SOStateMessage
     * @return String 
     */
    virtual static String parseStructToString(SOStateMessage messageClass);

    /**
     * @brief Set the Message object sortic state
     * 
     * @param object - &SOSTateMessage
     * @param messageId - unsigned int
     * @param messageConsignor - Consignor
     * @param messageState - String
     */
    virtual static void setMessage(SOStateMessage &object, unsigned int messageId, Consignor messageConsignor, String messageState);
};

#endif