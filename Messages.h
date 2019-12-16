/**
 * @file Messages.h
 * @author Philip Zellweger (philip.zellweger@hsr.ch)
 * @brief Serializing functions for the messagetypes
 * @version 0.1
 * @date 2019-11-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef MESSAGES_H__
#define MESSAGES_H__

#include <Arduino.h>
#include <ArduinoJson.h>
#include <memory>

#include "LogConfiguration.h"


/**
 * @brief Enum class holds all possible consignors
 * 
 * @todo use uids to get global id's
 * 
 */
enum class Consignor
{
    DEFUALTCONSIGNOR,
    SO1,
    SB1,
    SB2,
    SB3,
    SV1,
    SV2,
    SV3
};

/**
 * @brief Abstract parent class to serialize messages
 * 
 */
class Message
{
    private:


    public:

    unsigned int msgId = 0;                                     ///< id of the message
    MessageType msgType = MessageType::DEFAULTMESSAGETYPE;      ///< type of the message
    unsigned int msgLength = 0;                                 ///< length of the message
    Consignor msgConsignor = Consignor::DEFUALTCONSIGNOR;       ///< consignor of the message

    /**
     * @brief Construct a new Message object
     * 
     */
    Message();

    /**
     * @brief Destroy the Message object
     * 
     */
    virtual ~Message();

    /**
    * @brief Message type class holds all possible message types
    * 
    */
    enum class MessageType
    {
        DEFAULTMESSAGETYPE,
        Package,
        Error,
        SBAvailable,
        SBPosition,
        SBState,
        SBToSVHandshake,
        SVAvailable,
        SVPosition,
        SVState,
        SBToSOHandshake,
        SOPosition,
        SOState,
        SOInit,
        SOBuffer
    };

    /**
     * @brief Static function to serialize a JSON object to a class
     * 
     * @param payload 
     * @param length 
     * @return std::shared_ptr<Message> 
     */
    static std::shared_ptr<Message> translateJsonToStruct(const char* payload, unsigned int length); // MessageFactory

    /**
     * @brief Static function to serialize a message class to a publish string
     * 
     * @todo Delete this function and use direct function of spezific class
     * 
     * @param object 
     * @return String 
     */
    static String translateStructToString(std::shared_ptr<Message> object); // raus nehmen
    
    /**
     * @brief Virtual function to parse JSON object to a message class
     * 
     * @param doc 
     * @param error 
     */
    virtual void parseJSONToStruct(JsonDocument doc, DeserializationError error) = 0;   

    /**
     * @brief Virtual function to parse a message class to a publish string
     * 
     * @return String 
     */
    virtual String parseStructToString() = 0;
};



/**
 * @brief Child class to serialize package message
 * 
 */
class PackageMessage : public Message
{
private:
public:

    unsigned int packageId = 0;                 ///< id of the package
    String cargo = "-1";                        ///< cargo of the package
    String targetDest = "-1";                   ///< target destination of the package
    String targetReg = "-1";                    ///< target region of the package

    /**
     * @brief Construct a new Parse Package Message object
     * 
     */
    PackageMessage();

    /**
     * @brief Destroy the Parse Package Message object
     * 
     */
    ~PackageMessage();

    /**
     * @brief Parse JSON object to the PackageMessage class
     * 
     * @param doc 
     * @param error 
     */
    void parseJSONToStruct(JsonDocument doc, DeserializationError error) override;
    
    /**
     * @brief Parse the PackageMessage class to a publish string
     * 
     * @return String 
     */
    String parseStructToString() override;

    /**
     * @brief Set the PackageMessage object
     * 
     * @param messageId 
     * @param messageConsignor 
     * @param messagePackageId 
     * @param messageCargo 
     * @param messageTargetDest 
     * @param messageTargetReg 
     */
    void setMessage(unsigned int messageId, Consignor messageConsignor, unsigned int messagePackageId, String messageCargo, String messageTargetDest, String messageTargetReg);
};

/**
 * @brief Child class to serialize error message
 * 
 */
class ErrorMessage : public Message
{

private:
public:

    bool error;                     ///< error
    bool token;                     ///< token

    /**
     * @brief Construct a new Parse Error Message object
     * 
     */
    ErrorMessage();

    /**
     * @brief Destroy the Parse Error Message object
     * 
     */
    ~ErrorMessage();

    /**
     * @brief Parse JSON object to the ErrorMessage class
     * 
     * @param doc 
     * @param error 
     */
    void parseJSONToStruct(JsonDocument doc, DeserializationError error) override;
    
    /**
     * @brief Parse the ErrorMessage class to a publish string
     * 
     * @param messageClass - ErrorMessage
     * @return String 
     */
    String parseStructToString() override;

    /**
     * @brief Set the ErrorMessage object
     * 
     * @param messageId 
     * @param messageConsignor 
     * @param messageError 
     * @param messageToken 
     */
    void setMessage(unsigned int messageId, Consignor messageConsignor, bool messageError, bool messageToken);
};

/**
 * @brief Child class to serialize smartbox available message
 * 
 */
class SBAvailableMessage : public Message
{
private:
public:

    String sector = "-1";                           ///< sector of the smart box
    int line = -1;                                  ///< line of the smart box
    String targetReg = "-1";                        ///< target region of the smart box

    /**
     * @brief Construct a new Parse SB Available Message object
     * 
     */
    SBAvailableMessage();

    /**
     * @brief Destroy the My JSON Message SB Available object
     * 
     */
    ~SBAvailableMessage();
    
    /**
     * @brief Parse JSON object to the SBAvailableMessage class
     * 
     * @param doc 
     * @param error 
     */
    void parseJSONToStruct(JsonDocument doc, DeserializationError error) override;
    
    /**
     * @brief Parse the SBAvailableMessage class to a publish string
     * 
     * @param messageClass - SBAvailableMessage
     * @return String 
     */
    String parseStructToString() override;

    /**
     * @brief Set the SBAvailableMessage object
     * 
     * @param object - &SBAvailableMessage
     * @param messageId - unsigned int
     * @param messageConsignor - Consignor
     * @param messageSector - String
     * @param messageLine - int
     * @param messageTargetReg - String
     */
    void setMessage(unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine, String messageTargetReg);
};

/**
 * @brief Child class to serialize smartbox position message
 * 
 */
class SBPositionMessage : public Message
{
private:
public:

    String sector = "-1";                           ///< sector of the smart box
    int line = -1;                                  ///< line of the smart box

    /**
     * @brief Construct a new Parse S B Position Message object
     * 
     */
    SBPositionMessage();

    /**
     * @brief Destroy the Parse SB Position Message object
     * 
     */
    ~SBPositionMessage();

    /**
     * @brief Parse JSON object to the SBPositionMessage class
     * 
     * @param doc 
     * @param error 
     */
    void parseJSONToStruct(JsonDocument doc, DeserializationError error) override;
    
    /**
     * @brief Parse the SBPositionMessage class to a publish string
     * 
     * @return String 
     */
    String parseStructToString() override;

    /**
     * @brief Set the SBPositionMessage object
     * 
     * @param messageId 
     * @param messageConsignor 
     * @param messageSector 
     * @param messageLine 
     */
    void setMessage(unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine);
};

/**
 * @brief Child class to serialize smartbox state message
 * 
 */
class SBStateMessage : public Message
{
private:
public:

    String state = "-1";                            ///< state of the smart box

    /**
     * @brief Construct a new Parse S B State Message object
     * 
     */
    SBStateMessage();

    /**
     * @brief Destroy the Parse S B State Message object
     * 
     */
    ~SBStateMessage();

    /**
     * @brief Parse JSON object to the SBStateMessage class
     * 
     * @param doc - JsonDocument
     * @param error - DeserializationError
     * @return SBStateMessage*
     */
    void parseJSONToStruct(JsonDocument doc, DeserializationError error) override;
    
    /**
     * @brief Parse the SBStateMessage class to a publish string
     * 
     * @return String 
     */
    String parseStructToString() override;

    /**
     * @brief Set the SBStateMessage object
     * 
     * @param messageId 
     * @param messageConsignor 
     * @param messageState 
     */
    void setMessage(unsigned int messageId, Consignor messageConsignor, String messageState);
};

/**
 * @brief Child class to serialize smartbox to smartvehicle handshake message
 * 
 */
class SBToSVHandshakeMessage : public Message
{
private:   
public:

    String reck = "-1";                                     ///< request ID
    String ack = "-1";                                      ///< acknoledge ID
    String cargo = "-1";                                    ///< cargo
    String targetReg = "-1";                                ///< target region
    int line = -1;                                          ///< line

    /**
     * @brief Construct a new Parse SB to SV Handshake Message object
     * 
     */
    SBToSVHandshakeMessage();

    /**
     * @brief Destroy the Parse SB to SV Handshake Message object
     * 
     */
    ~SBToSVHandshakeMessage();

    /**
     * @brief Parse JSON object to the SBToSVHandshakeMessage class
     * 
     * @param doc 
     * @param error 
     */
    void parseJSONToStruct(JsonDocument doc, DeserializationError error) override;
    
    /**
     * @brief Parse the SBToSVHandshakeMessage class to a publish string
     * 
     * @return String 
     */
    String parseStructToString() override;

    /**
     * @brief Set the SBToSVHandshakeMessage object
     * 
     * @param messageId 
     * @param messageConsignor 
     * @param messageReck 
     * @param messageAck 
     * @param messageCargo 
     * @param messageLine 
     */
    void setMessage(unsigned int messageId, Consignor messageConsignor, String messageReck, String messageAck, String messageCargo, int messageLine);
};


/**
 * @brief Child class to serialize smartvehicle available message
 * 
 */
class SVAvailableMessage : public Message
{
private:
public:

    String sector = "-1";                               ///< sector of the smart vehicle
    int line = -1;                                      ///< line of the smart vehicle

    /**
     * @brief Construct a new Parse SV Available Message object
     * 
     */
    SVAvailableMessage();

    /**
     * @brief Destroy the Parse SV Available Message object
     * 
     */
    ~SVAvailableMessage();

    /**
     * @brief Parse JSON object to the SVAvailableMessage class
     * 
     * @param doc 
     * @param error 
     */
    void parseJSONToStruct(JsonDocument doc, DeserializationError error) override;
    
    /**
     * @brief Parse the SVAvailableMessage class to a publish string
     * 
     * @return String 
     */
    String parseStructToString() override;

    /**
     * @brief Set the SVAvailableMessage object
     * 
     * @param messageId 
     * @param messageConsignor 
     * @param messageSector 
     * @param messageLine 
     */
    void setMessage(unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine);
};

/**
 * @brief Child class to serialize smartvehicle position message
 * 
 */
class SVPositionMessage : public Message
{
private:
public:

    String sector = "-1";                               ///< sector of the smart vehicle
    int line = -1;                                      ///< line of the smart vehicle

    /**
     * @brief Construct a new Parse SV Position Message object
     * 
     */
    SVPositionMessage();

    /**
     * @brief Destroy the Parse SV Position Message object
     * 
     */
    ~SVPositionMessage();

    /**
     * @brief Parse JSON object to the SVPositionMessage class
     * 
     * @param doc 
     * @param error 
     */
    void parseJSONToStruct(JsonDocument doc, DeserializationError error) override;
    
    /**
     * @brief Parse the SVPositionMessage class to a publish string
     * 
     * @return String 
     */
    String parseStructToString() override;

    /**
     * @brief Set the SVPositionMessage object
     * 
     * @param messageId 
     * @param messageConsignor 
     * @param messageSector 
     * @param messageLine 
     */
    void setMessage(unsigned int messageId, Consignor messageConsignor, String messageSector, int messageLine);
};

/**
 * @brief Child class to serialize smartvehicle state message
 * 
 */
class SVStateMessage : public Message
{
private:
public:

    String state = "-1";                    ///< state of the smart vehicle

    /**
     * @brief Construct a new Parse SV State Message object
     * 
     */
    SVStateMessage();

    /**
     * @brief Destroy the Parse SV State Message object
     * 
     */
    ~SVStateMessage();

    /**
     * @brief Parse JSON object to the SVStateMessage class
     * 
     * @param doc 
     * @param error 
     */
    void parseJSONToStruct(JsonDocument doc, DeserializationError error) override;
    
    /**
     * @brief Parse the SVStateMessage class to a publish string
     * 
     * @return String 
     */
    String parseStructToString() override;

    /**
     * @brief Set the SVStateMessage object
     * 
     * @param messageId 
     * @param messageConsignor 
     * @param messageState 
     */
    void setMessage(unsigned int messageId, Consignor messageConsignor, String messageState);
};

/**
 * @brief Child class to serialize smartbox to sortic handshake message
 * 
 */
class SBToSOHandshakeMessage : public Message
{
private:
public:

    String req = "-1";                                      ///< request
    String ack = "-1";                                      ///< acknoledge
    String cargo = "-1";                                    ///< cargo
    String targetReg = "-1";                                ///< target region
    int line = -1;                                          ///< line

    /**
     * @brief Construct a new Parse SB to SO Handshake Message object
     * 
     */
    SBToSOHandshakeMessage();

    /**
     * @brief Destroy the Parse SB to SO Handshake Message object
     * 
     */
    ~SBToSOHandshakeMessage();

    /**
     * @brief Parse JSON object to the SBToSOHandshakeMessage class
     * 
     * @param doc 
     * @param error 
     */
    void parseJSONToStruct(JsonDocument doc, DeserializationError error) override;
    
    /**
     * @brief Parse the SBToSOHandshakeMessage class to a publish string
     * 
     * @return String 
     */
    String parseStructToString() override;

    /**
     * @brief Set the SBToSOHandshakeMessage object
     * 
     * @param messageId 
     * @param messageConsignor 
     * @param messageReck 
     * @param messageAck 
     * @param messageCargo 
     * @param messageTargetReg 
     * @param messageLine 
     */
    void setMessage(unsigned int messageId, Consignor messageConsignor, String messageReck, String messageAck = "-1", String messageCargo = "-1", String messageTargetReg = "-1", int messageLine = -1);
};

/**
 * @brief Child class to serialize sortic position message
 * 
 */
class SOPositionMessage : public Message
{
private:
public:

    int line = -1;                              ///< line of the sortic roboter

    /**
     * @brief Construct a new Parse SO Position Message object
     * 
     */
    SOPositionMessage();

    /**
     * @brief Destroy the Parse SO Position Message object
     * 
     */
    ~SOPositionMessage();

    /**
     * @brief Parse JSON object to the SOPositionMessage class
     * 
     * @param doc 
     * @param error 
     */
    void parseJSONToStruct(JsonDocument doc, DeserializationError error) override;

    /**
     * @brief Parse the SOPositionMessage class to a publish string
     * 
     * @return String 
     */
    String parseStructToString() override;

    /**
     * @brief Set the SOPositionMessage object
     * 
     * @param messageId 
     * @param messageConsignor 
     * @param messageLine 
     */
    void setMessage(unsigned int messageId, Consignor messageConsignor, int messageLine);
};

/**
 * @brief Child class to serialize sortic state message
 * 
 */
class SOStateMessage : public Message
{
private:
public:

    String state;                   ///< state of the sortic roboter

    /**
     * @brief Construct a new Parse SO State Message object
     * 
     */
    SOStateMessage();

    /**
     * @brief Destroy the Parse SO State Message object
     * 
     */
    ~SOStateMessage();

    /**
     * @brief Parse JSON object to the SOStateMessage class
     * 
     * @param doc 
     * @param error 
     */
    void parseJSONToStruct(JsonDocument doc, DeserializationError error) override;

    /**
     * @brief Parse the SOStateMessage class to a publish string
     * 
     * @return String 
     */
    String parseStructToString() override;

    /**
     * @brief Set the SOStateMessage object
     * 
     * @param messageId 
     * @param messageConsignor 
     * @param messageState 
     */
    void setMessage(unsigned int messageId, Consignor messageConsignor, String messageState);
};

/**
 * @brief Child class to serialize sortic state message
 * 
 */
class SOInitMessage : public Message
{
private:
public:

    String state;                           ///< state
    String req = "-1";                      ///< request
    String ack = "-1";                      ///< acknoledge
    String cargo = "-1";                    ///< cargo
    String targetReg = "-1";                ///< target region
    int line = -1;                          ///< line
    unsigned int packageId = 0;             ///< package id
    String targetDest = "-1";               ///< target destination
    bool error;                             ///< error
    bool token;                             ///< token

    /**
     * @brief Construct a new Parse SO Init Message object
     * 
     */
    SOInitMessage();

    /**
     * @brief Destroy the Parse SO Init Message Message object
     * 
     */
    ~SOInitMessage();

    /**
     * @brief Parse JSON object to the SOStateMessage class
     * 
     * @param doc 
     * @param error 
     */
    void parseJSONToStruct(JsonDocument doc, DeserializationError error) override;

    /**
     * @brief Parse the SOStateMessage class to a publish string
     * 
     * @return String 
     */
    String parseStructToString() override;

    /**
     * @brief Set the SOStateMessage object
     * 
     * @param messageId 
     * @param messageConsignor 
     * @param messageState 
     */
    void setMessage();
};

/**
 * @brief Child class to serialize error message
 * 
 */
class BufferMessage : public Message
{

private:
public:

    bool full;                      ///< full parameter
    bool cleared;                   ///< cleared parameter

    /**
     * @brief Construct a new Parse Error Message object
     * 
     */
    BufferMessage();

    /**
     * @brief Destroy the Parse Error Message object
     * 
     */
    ~BufferMessage();

    /**
     * @brief Parse JSON object to the BufferMessage class
     * 
     * @param doc 
     * @param error 
     */
    void parseJSONToStruct(JsonDocument doc, DeserializationError error) override;
    
    /**
     * @brief Parse the BufferMessage class to a publish string
     * 
     * @param messageClass - BufferMessage
     * @return String 
     */
    String parseStructToString() override;

    /**
     * @brief Set the BufferMessage object
     * 
     * @param messageId 
     * @param messageConsignor 
     * @param messageFull 
     * @param messageCleared 
     */
    void setMessage(unsigned int messageId, Consignor messageConsignor, bool messageFull, bool messageCleared);
};

#endif