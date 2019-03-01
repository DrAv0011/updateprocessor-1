#pragma once

#include <string>
#include <rapidxml.hpp>
#include <stdexcept>
#include <vector>

class Win10StoreNetwork {

public:
    struct CookieData {
        std::string encryptedData;
        std::string expiration;
    };
    struct UpdateInfo {
        std::string serverId;
        std::string updateId;
        std::string packageMoniker;

        void addXmlInfo(char* val);
    };
    struct SyncResult {
        std::vector<UpdateInfo> newUpdates;
    };

private:
    static const char* const NAMESPACE_SOAP;
    static const char* const NAMESPACE_ADDRESSING;
    static const char* const NAMESPACE_WSSECURITY_SECEXT;
    static const char* const NAMESPACE_WSSECURITY_UTILITY;
    static const char* const NAMESPACE_WU_AUTHORIZATION;

    static const char* const MINECRAFT_APP_ID;

    static const char* const PRIMARY_URL;

    static void formatTime(char* buf, size_t bufSize, time_t time);

    static void buildInstalledNonLeafUpdateIDs(rapidxml::xml_document<>& doc, rapidxml::xml_node<>& paramsNode);

    static void buildCommonHeader(rapidxml::xml_document<>& doc, rapidxml::xml_node<>& headNode, const char* action);

    static std::string buildCookieRequest();

    static std::string buildSyncRequest(CookieData const& cookie);

    static size_t httpOnWrite(char *ptr, size_t size, size_t nmemb, void *userdata);
    static void doHttpRequest(const char* url, const char* data, std::string& ret);

    static rapidxml::xml_node<>& firstNodeOrThrow(rapidxml::xml_node<>& parent, const char* name) {
        auto ret = parent.first_node(name);
        if (ret == nullptr)
            throw std::runtime_error("Node not found");
        return *ret;
    }

public:
    static CookieData fetchCookie();

    static SyncResult syncVersion(CookieData const& cookie);

};