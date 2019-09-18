#include "../IPTestAdministrator.h"

#include <gtest/gtest.h>
#include <core/core.h>

namespace WPEFramework {
namespace Tests {

    enum class TestEnum {
        ONE,
        TWO,
        THREE
    };    

    TEST(Core_Enumerate, CheckEntries)
    {
        Core::EnumerateType<TestEnum> testEnum;
        EXPECT_FALSE(testEnum.IsSet());
        for (int i = 0; i < 3; i++) {
            EXPECT_EQ(testEnum.Entry(i)->value, (i == 0 ? TestEnum::ONE : (i == 1 ? TestEnum::TWO : TestEnum::THREE)));
            EXPECT_STREQ(testEnum.Entry(i)->name, (i == 0 ? "ONE" : (i == 1 ? "TWO" : "THREE")));
        }
    }

    TEST(Core_Enumerate, Assignment)
    {
        Core::EnumerateType<TestEnum> testEnum;
        testEnum.Assignment(true, "three");
        EXPECT_FALSE(testEnum.IsSet());

        testEnum.Assignment(true, "THREE");
        EXPECT_TRUE(testEnum.IsSet());
        EXPECT_EQ(testEnum.Value(), TestEnum::THREE);
        EXPECT_STREQ(testEnum.Data(), "THREE");

        testEnum.Assignment(false, "three");
        EXPECT_EQ(testEnum.Value(), TestEnum::THREE);
        EXPECT_STREQ(testEnum.Data(), "THREE");

        testEnum.Assignment(false, "four");
        EXPECT_FALSE(testEnum.IsSet());

        testEnum.Clear();
        EXPECT_FALSE(testEnum.IsSet());
    }

    TEST(Core_Enumerate, FromEnumType)
    {
        TestEnum e = TestEnum::TWO;
        Core::EnumerateType<TestEnum> testEnum(e);
        EXPECT_EQ(testEnum, e);
        EXPECT_TRUE(testEnum.IsSet());
        EXPECT_EQ(testEnum.Value(), TestEnum::TWO);
        EXPECT_STREQ(testEnum.Data(), "TWO");
    }

    TEST(Core_Enumerate, FromValue)
    {
        Core::EnumerateType<TestEnum> testEnum(1);
        EXPECT_TRUE(testEnum.IsSet());
        EXPECT_EQ(testEnum.Value(), TestEnum::TWO);
        EXPECT_STREQ(testEnum.Data(), "TWO");

        testEnum = 3;
        EXPECT_FALSE(testEnum.IsSet());
    }

    TEST(Core_Enumerate, FromStringCaseSensitiveTrue)
    {
        Core::EnumerateType<TestEnum> testEnum("THREE");
        EXPECT_TRUE(testEnum.IsSet());
        EXPECT_EQ(testEnum.Value(), TestEnum::THREE);
        EXPECT_STREQ(testEnum.Data(), "THREE");
    }

    TEST(Core_Enumerate, FromStringCaseSensitiveFalse)
    {
        Core::EnumerateType<TestEnum> testEnum("three");
        EXPECT_FALSE(testEnum.IsSet());
    }

    TEST(Core_Enumerate, FromStringCaseInsensitive)
    {
        Core::EnumerateType<TestEnum> testEnum("three", false);
        EXPECT_TRUE(testEnum.IsSet());
        EXPECT_EQ(testEnum.Value(), TestEnum::THREE);
        EXPECT_STREQ(testEnum.Data(), "THREE");
    }

    TEST(Core_Enumerate, FromTextFragmentCaseSensitiveTrue)
    {
        Core::TextFragment testFragment("THREE");
        Core::EnumerateType<TestEnum> testEnum(testFragment);
        EXPECT_TRUE(testEnum.IsSet());
        EXPECT_EQ(testEnum.Value(), TestEnum::THREE);
        EXPECT_STREQ(testEnum.Data(), "THREE");
    }

    TEST(Core_Enumerate, FromTextFragmentCaseSensitiveFalse)
    {
        Core::TextFragment testFragment("three");
        Core::EnumerateType<TestEnum> testEnum(testFragment);
        EXPECT_FALSE(testEnum.IsSet());
    }

    TEST(Core_Enumerate, FromTextFragmentCaseInsensitive)
    {
        Core::TextFragment testFragment("three");
        Core::EnumerateType<TestEnum> testEnum(testFragment, false);
        EXPECT_TRUE(testEnum.IsSet());
        EXPECT_EQ(testEnum.Value(), TestEnum::THREE);
        EXPECT_STREQ(testEnum.Data(), "THREE");
    }
} // Tests
ENUM_CONVERSION_BEGIN(Tests::TestEnum)
    { Tests::TestEnum::ONE, _TXT("ONE") },
    { Tests::TestEnum::TWO, _TXT("TWO") },
    { Tests::TestEnum::THREE, _TXT("THREE") },
ENUM_CONVERSION_END(Tests::TestEnum)
} // WPEFramework
