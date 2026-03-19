#include "SmcParser.h"

SmcParser::SmcParser(RelationStore& store)
        : ctxt(store) {}

std::pair<bool, std::string> SmcParser::pars(std::string_view line) {
    ctxt.resetLine();

    std::vector<TokenStruct> tokens = tokenizer.getTokens(line);

    ContextFSM fsm(ctxt);
    fsm.enterStartState();
    std::string s(line);

    for (const auto& tok : tokens) {
        fsm.process(tok);
    }

    if (ctxt.getCommand() == Command::NONE) {
        return {false, "Unknown command"};;
    } else if (ctxt.getCommand() == Command::CREATE_LIST) {
        return ctxt.isLineOkCreate()
               ? std::make_pair(true, "Make create: " + s)
               : std::make_pair(false, "Create failed");
    } else if (ctxt.getCommand() == Command::CREATE_JOIN) {
        return ctxt.isLineOkJoin()
               ? std::make_pair(true, "Make join: " + s)
               : std::make_pair(false, "Join failed");
    }

    return {false, "Unknown command"};
}
