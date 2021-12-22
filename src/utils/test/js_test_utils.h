//--------------------------------------------------------------------------
// Copyright (C) 2021-2021 Cisco and/or its affiliates. All rights reserved.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License Version 2 as published
// by the Free Software Foundation.  You may not use, modify or distribute
// this program under any other version of the GNU General Public License.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//--------------------------------------------------------------------------
// js_test_utils.cc author Danylo Kyrylov <dkyrylov@cisco.com>

#ifndef JS_TEST_UTILS_H
#define JS_TEST_UTILS_H

#include <list>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

#include "utils/js_identifier_ctx.h"
#include "utils/js_normalizer.h"

constexpr int unlim_depth = -1;
constexpr int norm_depth = 65535;
constexpr int max_template_nesting = 4;
constexpr int max_bracket_depth = 256;
constexpr int max_scope_depth = 256;
static const std::unordered_set<std::string> s_ignored_ids { "console", "eval", "document" };

namespace snort
{
[[noreturn]] void FatalError(const char*, ...);
void trace_vprintf(const char*, TraceLevel, const char*, const Packet*, const char*, va_list);
}

class JSIdentifierCtxStub : public JSIdentifierCtxBase
{
public:
    JSIdentifierCtxStub() = default;

    const char* substitute(const char* identifier) override
    { return identifier; }
    virtual void add_alias(const char*, const std::string&&) override {}
    virtual const char* alias_lookup(const char* alias) const override
    { return alias; }
    bool is_ignored(const char*) const override
    { return false; }
    bool scope_push(JSProgramScopeType) override { return true; }
    bool scope_pop(JSProgramScopeType) override { return true; }
    void reset() override {}
    size_t size() const override { return 0; }
};

void test_scope(const char* context, std::list<JSProgramScopeType> stack);
void test_normalization(const char* source, const char* expected);
void test_normalization_bad(const char* source, const char* expected, JSTokenizer::JSRet eret);
typedef std::pair<const char*, const char*> PduCase;
// source, expected for a single PDU
void test_normalization(const std::vector<PduCase>& pdus);
typedef std::tuple<const char*,const char*, std::list<JSProgramScopeType>> ScopedPduCase;
// source, expected, and current scope type stack for a single PDU
void test_normalization(std::list<ScopedPduCase> pdus);

#endif // JS_TEST_UTILS_H
