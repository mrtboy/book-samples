#include <gtest/gtest.h>
#include <string>
#include <array>

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

struct ArabicToRomanMapping {
  unsigned int arabicNumber;
  std::string romanNumeral;
};

const std::size_t numberOfMappings = 1;
using ArabicToRomanMappings = std::array<ArabicToRomanMapping, numberOfMappings>;

const ArabicToRomanMappings arabicToRomanMappings = {
  { 100, "C" }
};

std::string convertArabicNumberToRomanNumeral(unsigned int arabicNumber) {
  std::string romanNumeral;
  while (arabicNumber >= arabicToRomanMappings[0].arabicNumber) {
    romanNumeral += arabicToRomanMappings[0].romanNumeral;
    arabicNumber -= arabicToRomanMappings[0].arabicNumber;
  }
  while (arabicNumber >= 10) {
    romanNumeral += "X";
    arabicNumber -= 10;
  }
  while (arabicNumber >= 1) {
    romanNumeral += "I";
    arabicNumber--;
  }
  return romanNumeral;
}

// Test code starts here...

class RomanNumeralAssert {
public:
  RomanNumeralAssert() = delete;
  explicit RomanNumeralAssert(const unsigned int arabicNumber) :
      arabicNumberToConvert(arabicNumber) { }
  void isConvertedToRomanNumeral(const std::string& expectedRomanNumeral) const {
    ASSERT_EQ(expectedRomanNumeral, convertArabicNumberToRomanNumeral(arabicNumberToConvert));
  }

private:
  const unsigned int arabicNumberToConvert;
};

RomanNumeralAssert assertThat(const unsigned int arabicNumber) {
  RomanNumeralAssert assert { arabicNumber };
  return assert;
}

TEST(ArabicToRomanNumeralsConverterTestCase, conversionOfArabicNumbersToRomanNumerals_Works) {
  assertThat(1).isConvertedToRomanNumeral("I");
  assertThat(2).isConvertedToRomanNumeral("II");
  assertThat(3).isConvertedToRomanNumeral("III");
  assertThat(10).isConvertedToRomanNumeral("X");
  assertThat(20).isConvertedToRomanNumeral("XX");
  assertThat(30).isConvertedToRomanNumeral("XXX");
  assertThat(33).isConvertedToRomanNumeral("XXXIII");
  assertThat(100).isConvertedToRomanNumeral("C");
  assertThat(200).isConvertedToRomanNumeral("CC");
  assertThat(300).isConvertedToRomanNumeral("CCC");
}
