/*
 * Copyright (C) 2013, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LATINIME_DYNAMIC_PT_UPDATING_HELPER_H
#define LATINIME_DYNAMIC_PT_UPDATING_HELPER_H

#include "defines.h"
#include "suggest/policyimpl/dictionary/structure/pt_common/pt_node_params.h"

namespace latinime {

class BufferWithExtendableBuffer;
class DynamicPtReadingHelper;
class PtNodeReader;
class PtNodeWriter;

class DynamicPtUpdatingHelper {
 public:
    DynamicPtUpdatingHelper(BufferWithExtendableBuffer *const buffer,
            const PtNodeReader *const ptNodeReader, PtNodeWriter *const ptNodeWriter)
            : mBuffer(buffer), mPtNodeReader(ptNodeReader), mPtNodeWriter(ptNodeWriter) {}

    ~DynamicPtUpdatingHelper() {}

    // Add a word to the dictionary. If the word already exists, update the probability.
    bool addUnigramWord(DynamicPtReadingHelper *const readingHelper,
            const int *const wordCodePoints, const int codePointCount, const int probability,
            const bool isNotAWord, const bool isBlacklisted, const int timestamp,
            bool *const outAddedNewUnigram);

    // Add a bigram relation from word0Pos to word1Pos.
    bool addBigramWords(const int word0Pos, const int word1Pos, const int probability,
            const int timestamp, bool *const outAddedNewBigram);

    // Remove a bigram relation from word0Pos to word1Pos.
    bool removeBigramWords(const int word0Pos, const int word1Pos);

    // Add a shortcut target.
    bool addShortcutTarget(const int wordPos, const int *const targetCodePoints,
            const int targetCodePointCount, const int shortcutProbability);

 private:
    DISALLOW_IMPLICIT_CONSTRUCTORS(DynamicPtUpdatingHelper);

    static const int CHILDREN_POSITION_FIELD_SIZE;

    BufferWithExtendableBuffer *const mBuffer;
    const PtNodeReader *const mPtNodeReader;
    PtNodeWriter *const mPtNodeWriter;

    bool createAndInsertNodeIntoPtNodeArray(const int parentPos, const int *const nodeCodePoints,
            const int nodeCodePointCount, const bool isNotAWord, const bool isBlacklisted,
            const int probability, const int timestamp, int *const forwardLinkFieldPos);

    bool setPtNodeProbability(const PtNodeParams *const originalPtNodeParams, const bool isNotAWord,
            const bool isBlacklisted, const int probability, const int timestamp,
            bool *const outAddedNewUnigram);

    bool createChildrenPtNodeArrayAndAChildPtNode(const PtNodeParams *const parentPtNodeParams,
            const bool isNotAWord, const bool isBlacklisted, const int probability,
            const int timestamp, const int *const codePoints, const int codePointCount);

    bool createNewPtNodeArrayWithAChildPtNode(const int parentPos, const int *const nodeCodePoints,
            const int nodeCodePointCount, const bool isNotAWord, const bool isBlacklisted,
            const int probability, const int timestamp);

    bool reallocatePtNodeAndAddNewPtNodes(
            const PtNodeParams *const reallocatingPtNodeParams, const int overlappingCodePointCount,
            const bool isNotAWord, const bool isBlacklisted, const int probabilityOfNewPtNode,
            const int timestamp, const int *const newNodeCodePoints,
            const int newNodeCodePointCount);

    const PtNodeParams getUpdatedPtNodeParams(const PtNodeParams *const originalPtNodeParams,
            const bool isNotAWord, const bool isBlacklisted, const bool isTerminal,
            const int parentPos, const int codePointCount,
            const int *const codePoints, const int probability) const;

    const PtNodeParams getPtNodeParamsForNewPtNode(const bool isNotAWord, const bool isBlacklisted,
            const bool isTerminal, const int parentPos,
            const int codePointCount, const int *const codePoints, const int probability) const;
};
} // namespace latinime
#endif /* LATINIME_DYNAMIC_PATRICIA_TRIE_UPDATING_HELPER_H */