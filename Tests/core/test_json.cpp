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

#include <gtest/gtest.h>
#include <core/core.h>

using namespace WPEFramework;

enum class CommandType {
    ENUM_1,
    ENUM_2,
    ENUM_3,
    ENUM_4
};

namespace WPEFramework {

    ENUM_CONVERSION_BEGIN(CommandType)
        { CommandType::ENUM_1, _TXT("enum_1") },
        { CommandType::ENUM_2, _TXT("enum_2") },
        { CommandType::ENUM_3, _TXT("enum_3") },
        { CommandType::ENUM_4, _TXT("enum_4") },
    ENUM_CONVERSION_END(CommandType)

}

class CommandParameters : public WPEFramework::Core::JSON::Container {

public:
    CommandParameters(const CommandParameters&) = delete;
    CommandParameters& operator=(const CommandParameters&) = delete;

    CommandParameters()
        : Core::JSON::Container()
        , G(00)
        , H(0)
        , I()
        , J()
    {
        Add(_T("g"), &G);
        Add(_T("h"), &H);
        Add(_T("i"), &I);
        Add(_T("j"), &J);
    }

    ~CommandParameters()
    {
    }

public:
    WPEFramework::Core::JSON::OctSInt16 G;
    WPEFramework::Core::JSON::DecSInt16 H;
    WPEFramework::Core::JSON::EnumType<CommandType> I;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::DecUInt16> J;
};

class CommandRequest : public WPEFramework::Core::JSON::Container {
public:
    CommandRequest(const CommandRequest&) = delete;
    CommandRequest& operator=(const CommandRequest&) = delete;

public:
    CommandRequest()
        : Core::JSON::Container()
        , A(0x0)
        , B()
        , C(0x0)
        , D(false)
        , E(00)
        , F()
    {
        Add(_T("a"), &A);
        Add(_T("b"), &B);
        Add(_T("c"), &C);
        Add(_T("d"), &D);
        Add(_T("e"), &E);
        Add(_T("f"), &F);
    }

    ~CommandRequest()
    {
    }

public:
    WPEFramework::Core::JSON::HexSInt32 A;
    WPEFramework::Core::JSON::String B;
    WPEFramework::Core::JSON::HexUInt32 C;
    WPEFramework::Core::JSON::Boolean D;
    WPEFramework::Core::JSON::OctUInt16 E;
    CommandParameters F;
};

class TestRequest : public WPEFramework::Core::JSON::Container {
public:
    TestRequest(const TestRequest&) = delete;
    TestRequest& operator=(const TestRequest&) = delete;

public:
    TestRequest()
        : Core::JSON::Container()
        , J()
        , K()
        , L()
        , M()
        , N()
        , O()
        , P()
        , Q()
    {
        Add(_T("j"), &J);
        Add(_T("k"), &K);
        Add(_T("l"), &L);
        Add(_T("m"), &M);
        Add(_T("n"), &N);
        Add(_T("o"), &O);
        Add(_T("p"), &P);
        Add(_T("q"), &Q);
    }

    ~TestRequest()
    {
    }

public:
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::DecUInt16> J;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::DecSInt16> K;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::String> L;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::HexUInt32> M;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::HexSInt32> N;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::Boolean> O;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::OctUInt16> P;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::OctSInt16> Q;
};

TEST(Core_JSON, DecUInt16ArrayWithSquareBrackets)
{
    string input = R"({"j":[12]})";
    string inputRequired = R"({"j":[12]})";
    string output;

    WPEFramework::Core::ProxyType<TestRequest> command = WPEFramework::Core::ProxyType<TestRequest>::Create();
    command->J.Add(WPEFramework::Core::JSON::DecUInt16(12, true));
    WPEFramework::Core::JSON::Tester<1, TestRequest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<TestRequest> received = WPEFramework::Core::ProxyType<TestRequest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, DecSInt16ArrayWithSquareBrackets)
{
    string input = R"({"k":[-12]})";
    string inputRequired = R"({"k":[-12]})";
    string output;

    WPEFramework::Core::ProxyType<TestRequest> command = WPEFramework::Core::ProxyType<TestRequest>::Create();
    command->K.Add(WPEFramework::Core::JSON::DecSInt16(-12, true));
    WPEFramework::Core::JSON::Tester<1, TestRequest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<TestRequest> received = WPEFramework::Core::ProxyType<TestRequest>::Create();
    parser.FromString(input, received);
}

TEST(DISABLED_Core_JSON, StringArrayWithSquareBrackets)
{
    string input = R"({"l":["Test"]})";
    string inputRequired = R"({"l":["Test"]})";
    string output;

    WPEFramework::Core::ProxyType<TestRequest> command = WPEFramework::Core::ProxyType<TestRequest>::Create();
    WPEFramework::Core::JSON::String str;
    str = string("Test");
    command->L.Add(str);
    WPEFramework::Core::JSON::Tester<1, TestRequest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<TestRequest> received = WPEFramework::Core::ProxyType<TestRequest>::Create();
    parser.FromString(input, received);
}

TEST(DISABLED_Core_JSON, HexUInt32ArrayWithSquareBrackets)
{
    string input = R"({"m":["0x8"]})";
    string inputRequired = R"({"m":["0x8"]})";
    string output;

    WPEFramework::Core::ProxyType<TestRequest> command = WPEFramework::Core::ProxyType<TestRequest>::Create();
    command->M.Add(WPEFramework::Core::JSON::HexUInt32(8, true));
    WPEFramework::Core::JSON::Tester<1, TestRequest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<TestRequest> received = WPEFramework::Core::ProxyType<TestRequest>::Create();
    parser.FromString(input, received);
}

TEST(DISABLED_Core_JSON, HexSInt32ArrayWithSquareBrackets)
{
    string input = R"({"n":["-0x8"]})";
    string inputRequired = R"({"n":["-0x8"]})";
    string output;

    WPEFramework::Core::ProxyType<TestRequest> command = WPEFramework::Core::ProxyType<TestRequest>::Create();
    command->N.Add(WPEFramework::Core::JSON::HexSInt32(-8, true));
    WPEFramework::Core::JSON::Tester<1, TestRequest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<TestRequest> received = WPEFramework::Core::ProxyType<TestRequest>::Create();
    parser.FromString(input, received);
}

TEST(DISABLED_Core_JSON, OctUInt16ArrayWithSquareBrackets)
{
    string input = R"({"p":["014"]})";
    string inputRequired = R"({"p":["014"]})";
    string output;

    WPEFramework::Core::ProxyType<TestRequest> command = WPEFramework::Core::ProxyType<TestRequest>::Create();
    command->P.Add(WPEFramework::Core::JSON::OctUInt16(12, true));
    WPEFramework::Core::JSON::Tester<1, TestRequest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<TestRequest> received = WPEFramework::Core::ProxyType<TestRequest>::Create();
    parser.FromString(input, received);
}

TEST(DISABLED_Core_JSON, OctSInt16ArrayWithSquareBrackets)
{
    string input = R"({"q":["-014"]})";
    string inputRequired = R"({"q":["-014"]})";
    string output;

    WPEFramework::Core::ProxyType<TestRequest> command = WPEFramework::Core::ProxyType<TestRequest>::Create();
    command->Q.Add(WPEFramework::Core::JSON::OctSInt16(-12, true));
    WPEFramework::Core::JSON::Tester<1, TestRequest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<TestRequest> received = WPEFramework::Core::ProxyType<TestRequest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, simpleSet)
{
    {
        //Tester
        string input = R"({"a":"-0x5A","b":"TestIdentifier","c":"0x5A","d":true,"e":"014","f":{"g":"-014","h":"-44","i":"enum_4","j":["6","14","22"]}})";
        string inputRequired = R"({"a":"-0x5A","b":"TestIdentifier","c":"0x5A","d":true,"e":"014","f":{"g":"-014","h":-44,"i":"enum_4","j":[6,14,22]}})";
        string output;
        WPEFramework::Core::ProxyType<CommandRequest> command = WPEFramework::Core::ProxyType<CommandRequest>::Create();
        command->A = -90;
        command->B = _T("TestIdentifier");
        command->C = 90;
        command->D = true;
        command->E = 12;
        command->F.G = -12;
        command->F.H = -44;
        command->F.I = CommandType::ENUM_4;
        command->F.J.Add(WPEFramework::Core::JSON::DecUInt16(6, true));
        command->F.J.Add(WPEFramework::Core::JSON::DecUInt16(14, true));
        command->F.J.Add(WPEFramework::Core::JSON::DecUInt16(22, true));
        WPEFramework::Core::JSON::Tester<1, CommandRequest> parser;

        //ToString
        parser.ToString(command, output);
        ASSERT_STREQ(inputRequired.c_str(), output.c_str());

        //FromString
        WPEFramework::Core::ProxyType<CommandRequest> received = WPEFramework::Core::ProxyType<CommandRequest>::Create();
        parser.FromString(input, received);
        output.clear();
        parser.ToString(received, output);
        ASSERT_STREQ(inputRequired.c_str(), output.c_str());

        parser.FromString(inputRequired, received);
        output.clear();
        parser.ToString(received, output);
        ASSERT_STREQ(inputRequired.c_str(), output.c_str());

        //ArrayType Iterator
        WPEFramework::Core::JSON::ArrayType<Core::JSON::DecUInt16>::Iterator settings(command->F.J.Elements());
        for(int i = 0; settings.Next(); i++)
            ASSERT_EQ(settings.Current().Value(), command->F.J[i]);
        //null test
        input = R"({"a":null,"b":null,"c":"0x5A","d":null,"f":{"g":"-014","h":-44}})";
        parser.FromString(input, received);
        output.clear();
        parser.ToString(received, output);
        //ASSERT_STREQ(input.c_str(), output.c_str());
    }
    //JsonObject and JsonValue
    {
        string input = R"({"a":"-0x5A","b":"TestIdentifier","c":"0x5A","d":true,"e":"014","f":{"g":"-014","h":-44,"i":"enum_4","j":[6,14,22]}})";
        JsonObject command;
        command.FromString(input);
        string output;
        command.ToString(output);
        ASSERT_STREQ(input.c_str(), output.c_str());

        JsonObject object;
        object["g"] = "-014";
        object["h"] = -44;
        object["i"] = "enum_4";
        JsonArray arrayValue;
        arrayValue.Add(6);
        arrayValue.Add(14);
        arrayValue.Add(22);
        object["j"] = arrayValue;
        JsonObject demoObject;
        demoObject["a"] = "-0x5A";
        demoObject["b"] = "TestIdentifier";
        demoObject["c"] = "0x5A";
        demoObject["d"] = true;
        demoObject["e"] = "014";
        demoObject["f"] = object;
        string serialized;
        demoObject.ToString(serialized);
        ASSERT_STREQ(input.c_str(), serialized.c_str());

        JsonObject::Iterator index = demoObject.Variants();
        while (index.Next()) {
            JsonValue value(demoObject.Get(index.Label()));
            ASSERT_EQ(value.Content(), index.Current().Content());
            ASSERT_STREQ(value.Value().c_str(), index.Current().Value().c_str());
        }
    }
}
