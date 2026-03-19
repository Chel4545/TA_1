#ifndef LAB1_SMCPARSER_H
#define LAB1_SMCPARSER_H

#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "../IPars.h"
#include "../Store/RelationStore.h"
#include "SmcClass.h"
#include "Tokenizer.h"
#include "ContextFSM.h"

class SmcParser : public IPars {
private:
    SmcClass ctxt;
    Tokenizer tokenizer;

public:
    explicit SmcParser(RelationStore& store);

    std::pair<bool, std::string> pars(std::string_view line) override;
};

#endif
