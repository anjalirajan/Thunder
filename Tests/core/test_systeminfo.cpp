/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "../IPTestAdministrator.h"

#include <fstream>
#include <gtest/gtest.h>
#include <core/core.h>

namespace WPEFramework {
namespace Tests {

enum class Purpose {
    MEM,
    SWAP,
    HOST
};

enum class Funcion {
    TOTAL,
    FREE,
    UNKNOWN
};

std::string getMem(std::string result, Funcion func)
{
    std::string word = "";
    int i = 1;
    std::stringstream iss(result);
    while (iss >> result)
    {
        if(i == 2 && func == Funcion::TOTAL){
            word.assign(result);
            break;
        }/* //retrieves the free memory
        if(i == 4 && (func == Funcion::FREE)){
            word.assign(result);
            break;
        }*/
        i++;
    }
    return word;
}

std::string exec(const char* cmd, Purpose purpose, Funcion func) {
    char buffer[128];
    std::string result = "";
    std::string word = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result = buffer;
            if (purpose == Purpose::MEM) {
                if (result.find("Mem:") != std::string::npos) {
                    word = getMem(result, func);
                }
            } else if (purpose == Purpose::SWAP) {
                if (result.find("Swap:") != std::string::npos) {
                    word = getMem(result, func);
                }
            } else if (purpose == Purpose::HOST) {
                word.assign(result);
                break;
            }
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return word;
}

float getUptime() {
    std::string uptime;
    std::ifstream file("/proc/uptime");
    while(file >> uptime)
        return (ceil(stof(uptime)));
    return 0;
}

TEST(Core_SystemInfo, systemInfo)
{
    const uint8_t* rawDeviceId (WPEFramework::Core::SystemInfo::Instance().RawDeviceId());

    string id (WPEFramework::Core::SystemInfo::Instance().Id(rawDeviceId, 0xFF));
    string id1 (WPEFramework::Core::SystemInfo::Instance().Id(rawDeviceId, 0x11));
    string id2 (WPEFramework::Core::SystemInfo::Instance().Id(rawDeviceId, 0x7));

    std::string cmd = "hostname";
    string hostname = exec(cmd.c_str(), Purpose::HOST, Funcion::UNKNOWN).c_str();
    hostname.erase(std::remove(hostname.begin(), hostname.end(), '\n'), hostname.end());
    EXPECT_STREQ(WPEFramework::Core::SystemInfo::Instance().GetHostName().c_str(), hostname.c_str());

    cmd = "free -b";
    EXPECT_EQ(WPEFramework::Core::SystemInfo::Instance().GetPageSize(),getpagesize());
    EXPECT_EQ(WPEFramework::Core::SystemInfo::Instance().GetTotalRam(), stoi(exec(cmd.c_str(), Purpose::MEM, Funcion::TOTAL)));

    //EXPECT_EQ(WPEFramework::Core::SystemInfo::Instance().GetFreeRam(),stoi(exec(cmd.c_str(),Purpose::MEM, Funcion::FREE)));
    WPEFramework::Core::SystemInfo::Instance().GetFreeRam(); //Returns the instant snapshot of the free memory at that moment, hence can't verify it's value.

    EXPECT_EQ(WPEFramework::Core::SystemInfo::Instance().GetUpTime(),getUptime());

    WPEFramework::Core::SystemInfo::Instance().Ticks();

    WPEFramework::Core::SystemInfo::Instance().GetCpuLoad();

    std::string variable = "TEST_VARIABLE";
    std::string value = "test value";
    std::string getValue;
    bool forced = true;
    WPEFramework::Core::SystemInfo::Instance().SetEnvironment(variable, value, forced);
    WPEFramework::Core::SystemInfo::Instance().GetEnvironment(variable, getValue);

    EXPECT_STREQ(getValue.c_str(),value.c_str());
}

TEST(Core_SystemInfo, memorySnapShot)
{
    WPEFramework::Core::SystemInfo::MemorySnapshot snapshot = WPEFramework::Core::SystemInfo::Instance().TakeMemorySnapshot();
    snapshot.AsJSON();
    std::string cmd = "free -k";
    EXPECT_EQ(snapshot.Total(), stoi(exec(cmd.c_str(), Purpose::MEM, Funcion::TOTAL)));
    snapshot.Free(); //Returns the instant snapshot of the free memory at that moment, hence can't verify it's value.
    snapshot.Available();//Returns the instant snapshot of the available memory at that moment, hence can't verify it's value.
    snapshot.Cached();

    EXPECT_EQ(snapshot.SwapTotal(),stoi(exec(cmd.c_str(), Purpose::SWAP, Funcion::TOTAL)));
    snapshot.SwapFree();
    snapshot.SwapCached();
}
} // Tests

ENUM_CONVERSION_BEGIN(Tests::Purpose)
    { WPEFramework::Tests::Purpose::MEM, _TXT("mem") },
    { WPEFramework::Tests::Purpose::SWAP, _TXT("swap") },
    { WPEFramework::Tests::Purpose::HOST, _TXT("host") },
ENUM_CONVERSION_END(Tests::Purpose)

ENUM_CONVERSION_BEGIN(Tests::Funcion)
    { WPEFramework::Tests::Funcion::TOTAL, _TXT("total") },
    { WPEFramework::Tests::Funcion::FREE, _TXT("free") },
ENUM_CONVERSION_END(Tests::Funcion)

} // WPEFramework
