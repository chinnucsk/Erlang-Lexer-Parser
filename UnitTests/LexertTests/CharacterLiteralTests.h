#pragma once
#include <boost/test/unit_test.hpp>
#include "TestUtil.h"
#include <ErlangTokens.h>
#include <string>
#include <utility>

BOOST_AUTO_TEST_SUITE( CharacterLiteralTests )

using namespace TestUtil;
using std::wstring;
using std::pair;
using std::make_pair;
using std::transform;
using std::for_each;

BOOST_AUTO_TEST_CASE( CharacterLiteralsTest )
{
    vector<wstring> charLiterals;
    PopulateASCIICharacterCodes(charLiterals, make_pair(32, 127), wstring(L"$"));

    vector<pair<unsigned int, const wchar_t*>> pairs;
    transform(charLiterals.begin(), charLiterals.end(), back_inserter(pairs),
              [](const wstring& refString) { return make_pair(CHARACTERLITERAL, refString.c_str()); });

    VerifyPairs(pairs.begin(), pairs.end());
}

BOOST_AUTO_TEST_CASE( EscapedControlCodesCharacterLiteralsTest )
{
    VerifyEscapedControlCodes(CHARACTERLITERAL, wstring(L"$"), wstring(L""));
}

BOOST_AUTO_TEST_CASE( EscapedOctalCharacterLiteralsTest )
{
    VerifyEscapedOctalDigits(CHARACTERLITERAL, wstring(L"$"), wstring(L""));
}

BOOST_AUTO_TEST_CASE( InvalidCharacterLiteralTests )
{
    vector<wstring> charLiterals;
    PopulateASCIICharacterCodes(charLiterals, make_pair(0, 32), wstring(L"$"));

    wstring str(L"$");
    str += static_cast<wchar_t>(127);

    charLiterals.push_back(str);

    for_each(charLiterals.begin(), charLiterals.end(),
             [](const wstring& refItem) 
             {
                 TokenVector expectedTokens;
                 VerifyLex(refItem, expectedTokens, false /*shouldSucceed*/);
             });
}

BOOST_AUTO_TEST_SUITE_END()