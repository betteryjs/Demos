//
// Created by yjs on 2022/7/19.
//

#include <cpr/cpr.h>
#include <iostream>
#include <string>
#include "include/json.hpp"
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using json = nlohmann::json;
using namespace std;


string getIP(const string & hostName){

    char   *ptr, **pptr;
    struct hostent *hptr;
    char   str[32];
    string ip{};
    if((hptr = gethostbyname(hostName.c_str())) == NULL)
    {
        printf(" gethostbyname error for host:%s\n", ptr);
        return 0;
    }

    if(hptr->h_addrtype== AF_INET || hptr->h_addrtype==AF_INET6){
        inet_ntop(hptr->h_addrtype, hptr->h_addr, str, sizeof(str) );
    }
    ip=string (str);
    return ip;
}


int main(int argc, char** argv ) {
    if(argc!=2){
        cerr<< "参数必须是两个"<<endl;
    }
    string ip{argv[1]};
//    string ip{};
//    if((!hostname.empty()) && hostname[0] ){
//        // is a url
//        ip= getIP(hostname);
//    }

    ifstream key("key.json");
    json keys_json;
    key>> keys_json;
    string  APPCODE=keys_json.at("APPCODE").get<string>();
    cpr::Response response = cpr::Get(cpr::Url{"https://hcapi20.market.alicloudapi.com/ip"},
                                      cpr::Header{{"accept", "application/json"},{"Authorization","APPCODE "+APPCODE}},
                                      cpr::Parameters{{"ip", ip}});

    // application/json; charset=utf-8
    if(response.status_code==200){
        auto response_json =json::parse(response.text);
        if(response_json.at("ret").get<int>()==200  && response_json.at("msg").get<string>()=="success"){
            // 216.58.220.132
            string res{};
            res+=" \t "+response_json.at("data").at("city").get<string>()+" ";
            res+=" \t "+response_json.at("data").at("country_id").get<string>()+" ";
            res+=" \t "+response_json.at("data").at("isp").get<string>()+" ";
            res+=" \t "+response_json.at("data").at("ip").get<string>()+" ";
            cout << res<<endl;

//            auto res=response_json.at("data")
//            cout << "country is \t"<< response_json.at("data").at("city").get<string>()<<endl;
//            cout << "country_id is \t"<< response_json.at("data").at("country_id").get<string>()<<endl;
//            cout << "ip is \t"<< response_json.at("data").at("ip").get<string>()<<endl;
//            cout << "isp is \t"<< response_json.at("data").at("isp").get<string>()<<endl;


        }

    }else if(response.status_code==403){
        cout << "response.status_code  is "<< response.status_code<<endl;
    }
    else{
        cerr << "response.status_code  is "<< response.status_code<<endl;
        cerr << "response.text  is "<< response.text<<endl;
    }
    // {
    //  "area": "华东",
    //  "city": "南京",
    //  "city_id": "320100",
    //  "country": "中国",
    //  "country_id": "CN",
    //  "district": "",
    //  "district_id": "",
    //  "ip": "36.152.44.96",
    //  "isp": "移动",
    //  "long_ip": "613952608",
    //  "region": "江苏",
    //  "region_id": "320000"
    //}

}
