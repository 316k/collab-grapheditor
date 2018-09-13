#pragma once

#include <vector>
#include <string>

#include "collabdata/custom/SimpleGraph.h"


namespace utils {


/**
 * @brief
 * Collect words in the range [@c first, @c last).
 *
 * @details
 * Words are separated by one or more unquoted spaces.
 * Spaces between double quotes are not separators.
 * They are instead part of a word.
 *
 * @warning
 * @c first and @c last must form a valid range.
 * Behavior is undefined if this is not the case.
 *
 * @warning
 * Quotes are assumed to be paired.
 * A warning is issued if the range contains an odd number of quotes.
 *
 * @see
 * www.physicsforums.com/threads/c-function-to-split-a-string-by-whitespace-ignoring-any-whitespace-in-quotes.778920/
 *
 * @return
 * Collected words as a vector of strings.
 */
std::vector<std::string> split_no_quotes(
    const std::string::const_iterator first, //!< Start of range.
    const std::string::const_iterator last);  //!< End of range.


} // namespace utils


class SGraphOpHandlerDebug : public collab::SimpleGraph::OpHandler {
    public:
        void handleOperation(const collab::SimpleGraph::VertexAddOperation &op) override;
        void handleOperation(const collab::SimpleGraph::VertexRemoveOperation &op) override;
        void handleOperation(const collab::SimpleGraph::EdgeAddOperation &op) override;
        void handleOperation(const collab::SimpleGraph::EdgeRemoveOperation &op) override;
        void handleOperation(const collab::SimpleGraph::AttributeAddOperation &op) override;
        void handleOperation(const collab::SimpleGraph::AttributeRemoveOperation &op) override;
        void handleOperation(const collab::SimpleGraph::AttributeSetOperation &op) override;
};


class SGraphOpObserverDebug : public collab::OperationObserver {
    private:
        SGraphOpHandlerDebug _opHandler;
    public:
        SGraphOpObserverDebug() = default;
        void onOperation(const collab::Operation &op) override;
};


