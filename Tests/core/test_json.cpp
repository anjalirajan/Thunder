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

class ArrayTypeTest : public WPEFramework::Core::JSON::Container {
public:
    ArrayTypeTest(const ArrayTypeTest&) = delete;
    ArrayTypeTest& operator=(const ArrayTypeTest&) = delete;

public:
    ArrayTypeTest()
        : Core::JSON::Container()
        , A()
        , B()
        , C()
        , D()
        , E()
        , F()
        , G()
        , H()
        , I()
        , J()
        , K()
        , L()
        , M()
        , N()
        , O()
        , P()
        , Q()
        , R()
        , S()
        , T()
        , U()
        , V()
        , W()
        , X()
        , Y()
        , Z()
        , AA()
        , AB()
    {
        Add(_T("a"), &A);
        Add(_T("b"), &B);
        Add(_T("c"), &C);
        Add(_T("d"), &D);
        Add(_T("e"), &E);
        Add(_T("f"), &F);
        Add(_T("g"), &G);
        Add(_T("h"), &H);
        Add(_T("i"), &I);
        Add(_T("j"), &J);
        Add(_T("k"), &K);
        Add(_T("l"), &L);
        Add(_T("m"), &M);
        Add(_T("n"), &N);
        Add(_T("o"), &O);
        Add(_T("p"), &P);
        Add(_T("q"), &Q);
        Add(_T("r"), &R);
        Add(_T("s"), &S);
        Add(_T("t"), &T);
        Add(_T("u"), &U);
        Add(_T("v"), &V);
        Add(_T("w"), &W);
        Add(_T("x"), &X);
        Add(_T("y"), &Y);
        Add(_T("z"), &Z);
        Add(_T("aa"), &AA);
        Add(_T("ab"), &AB);
    }

    ~ArrayTypeTest()
    {
    }

public:
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::DecUInt8> A;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::DecSInt8> B;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::DecUInt16> C;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::DecSInt16> D;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::DecUInt32> E;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::DecSInt32> F;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::DecUInt64> G;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::DecSInt64> H;

    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::HexUInt8> I;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::HexSInt8> J;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::HexUInt16> K;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::HexSInt16> L;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::HexUInt32> M;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::HexSInt32> N;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::HexUInt64> O;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::HexSInt64> P;

    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::OctUInt8> Q;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::OctSInt8> R;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::OctUInt16> S;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::OctSInt16> T;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::OctUInt32> U;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::OctSInt32> V;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::OctUInt64> W;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::OctSInt64> X;

    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::String> Y;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::Boolean> Z;

    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::Float> AA;
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::Double> AB;
};

TEST(Core_JSON, DecUInt8ArrayWithSquareBrackets)
{
    string input = R"({"a":[12]})";
    string inputRequired = R"({"a":[12]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->A.Add(WPEFramework::Core::JSON::DecUInt8(12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, DecSInt8ArrayWithSquareBrackets)
{
    string input = R"({"b":[-12]})";
    string inputRequired = R"({"b":[-12]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->B.Add(WPEFramework::Core::JSON::DecSInt8(-12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, DecUInt16ArrayWithSquareBrackets)
{
    string input = R"({"c":[12]})";
    string inputRequired = R"({"c":[12]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->C.Add(WPEFramework::Core::JSON::DecUInt16(12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, DecSInt16ArrayWithSquareBrackets)
{
    string input = R"({"d":[-12]})";
    string inputRequired = R"({"d":[-12]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->D.Add(WPEFramework::Core::JSON::DecSInt16(-12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, DecUInt32ArrayWithSquareBrackets)
{
    string input = R"({"e":[12]})";
    string inputRequired = R"({"e":[12]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->E.Add(WPEFramework::Core::JSON::DecUInt32(12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, DecSInt32ArrayWithSquareBrackets)
{
    string input = R"({"f":[-12]})";
    string inputRequired = R"({"f":[-12]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->F.Add(WPEFramework::Core::JSON::DecSInt32(-12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, DecUInt64ArrayWithSquareBrackets)
{
    string input = R"({"g":[12]})";
    string inputRequired = R"({"g":[12]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->G.Add(WPEFramework::Core::JSON::DecUInt64(12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, DecSInt64ArrayWithSquareBrackets)
{
    string input = R"({"h":[-12]})";
    string inputRequired = R"({"h":[-12]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->H.Add(WPEFramework::Core::JSON::DecSInt64(-12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, HexUInt8ArrayWithSquareBrackets)
{
    string input = R"({"i":["0x8"]})";
    string inputRequired = R"({"i":["0x8"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->I.Add(WPEFramework::Core::JSON::HexUInt8(8, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, HexSInt8ArrayWithSquareBrackets)
{
    string input = R"({"j":["-0x8"]})";
    string inputRequired = R"({"j":["-0x8"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->J.Add(WPEFramework::Core::JSON::HexSInt8(-8, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, HexUInt16ArrayWithSquareBrackets)
{
    string input = R"({"k":["0x8"]})";
    string inputRequired = R"({"k":["0x8"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->K.Add(WPEFramework::Core::JSON::HexUInt16(8, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, HexSInt16ArrayWithSquareBrackets)
{
    string input = R"({"l":["-0x8"]})";
    string inputRequired = R"({"l":["-0x8"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->L.Add(WPEFramework::Core::JSON::HexSInt16(-8, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, HexUInt32ArrayWithSquareBrackets)
{
    string input = R"({"m":["0x8"]})";
    string inputRequired = R"({"m":["0x8"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->M.Add(WPEFramework::Core::JSON::HexUInt32(8, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, HexSInt32ArrayWithSquareBrackets)
{
    string input = R"({"n":["-0x8"]})";
    string inputRequired = R"({"n":["-0x8"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->N.Add(WPEFramework::Core::JSON::HexSInt32(-8, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, HexUInt64ArrayWithSquareBrackets)
{
    string input = R"({"o":["0x8"]})";
    string inputRequired = R"({"o":["0x8"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->O.Add(WPEFramework::Core::JSON::HexUInt64(8, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, HexSInt64ArrayWithSquareBrackets)
{
    string input = R"({"p":["-0x8"]})";
    string inputRequired = R"({"p":["-0x8"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->P.Add(WPEFramework::Core::JSON::HexSInt64(-8, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, OctUInt8ArrayWithSquareBrackets)
{
    string input = R"({"q":["014"]})";
    string inputRequired = R"({"q":["014"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->Q.Add(WPEFramework::Core::JSON::OctUInt8(12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, OctSInt8ArrayWithSquareBrackets)
{
    string input = R"({"r":["014"]})";
    string inputRequired = R"({"r":["014"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->R.Add(WPEFramework::Core::JSON::OctSInt8(12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, OctUInt16ArrayWithSquareBrackets)
{
    string input = R"({"s":["014"]})";
    string inputRequired = R"({"s":["014"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->S.Add(WPEFramework::Core::JSON::OctUInt16(12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, OctSInt16ArrayWithSquareBrackets)
{
    string input = R"({"t":["-014"]})";
    string inputRequired = R"({"t":["-014"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->T.Add(WPEFramework::Core::JSON::OctSInt16(-12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, OctUInt32ArrayWithSquareBrackets)
{
    string input = R"({"u":["014"]})";
    string inputRequired = R"({"u":["014"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->U.Add(WPEFramework::Core::JSON::OctUInt32(12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, OctSInt32ArrayWithSquareBrackets)
{
    string input = R"({"v":["-014"]})";
    string inputRequired = R"({"v":["-014"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->V.Add(WPEFramework::Core::JSON::OctSInt32(-12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, OctUInt64ArrayWithSquareBrackets)
{
    string input = R"({"w":["014"]})";
    string inputRequired = R"({"w":["014"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->W.Add(WPEFramework::Core::JSON::OctUInt64(12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, OctSInt64ArrayWithSquareBrackets)
{
    string input = R"({"x":["-014"]})";
    string inputRequired = R"({"x":["-014"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->X.Add(WPEFramework::Core::JSON::OctSInt64(-12, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, StringArrayWithSquareBrackets)
{
    string input = R"({"y":["Test"]})";
    string inputRequired = R"({"y":["Test"]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    WPEFramework::Core::JSON::String str;
    str = string("Test");
    command->Y.Add(str);
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, BooleanArrayWithSquareBrackets)
{
    string input = R"({"z":[true]})";
    string inputRequired = R"({"z":[true]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    WPEFramework::Core::JSON::Boolean boolean;
    boolean = true;
    command->Z.Add(boolean);
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, FloatArrayWithSquareBrackets)
{
    string input = R"({"aa":[247.39]})";
    string inputRequired = R"({"aa":[247.39]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->AA.Add(WPEFramework::Core::JSON::Float(247.398f,true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    parser.FromString(input, received);
}

TEST(Core_JSON, DoubleArrayWithSquareBrackets)
{
    string input = R"({"ab":[32.24]})";
    string inputRequired = R"({"ab":[32.24]})";
    string output;

    WPEFramework::Core::ProxyType<ArrayTypeTest> command = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
    command->AB.Add(WPEFramework::Core::JSON::Double(32.24, true));
    WPEFramework::Core::JSON::Tester<1, ArrayTypeTest> parser;

    //ToString
    parser.ToString(command, output);
    ASSERT_STREQ(inputRequired.c_str(), output.c_str());

    //FromString
    WPEFramework::Core::ProxyType<ArrayTypeTest> received = WPEFramework::Core::ProxyType<ArrayTypeTest>::Create();
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
