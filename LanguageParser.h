#include <string>
#include <vector>
#include <map>
//extern "C" {
//	#include <julius/juliuslib.h>
//}
#ifdef min
#undef min //I have no idea what I'm undef-ing, but it fails to compile unless this is here.
#endif

#ifndef COMPSCI3307_PROJECT_LANGUAGEPARSER_H
#define COMPSCI3307_PROJECT_LANGUAGEPARSER_H
/*!
 * A collection of static helper functions and data structures for parsing English commands and organising the output in an easily-interpreted
 * fashion, to enable easy selection and execution of commands wherever they are best executed.
 *
 * @author Juhani Dickinson
 * @brief Static functions and data structures for natural language command parsing.
 */

class LanguageParser{
    public:
        //static void initCustomTargets();

        enum struct ACTIONS{ CREATE, DELETE, EDIT, START, STOP, REMIND, BADACTION };
        enum struct COMPLEMENT_TYPE{ TIME_LEN, TIME_REL, TIME_START, TIME_END, TEXT, EMPTY };
        enum struct DAY_OF_WEEK{ MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY, TOMORROW, NO_DATE };
        typedef struct{
            ACTIONS action;
            std::string target;
            int param1, param2;
            std::string param3;
            DAY_OF_WEEK dayOfWeek;
            COMPLEMENT_TYPE param1Type, param2Type, param3Type;
        } Command;

        /*!Takes a spoken or word-format number, or a spoken or word-format time and converts it into a mathematical number.
         *
         * @authors
         * @brief Converts a word-format number to long double.
         * @param number Word-format number to be converted, must be all lowercase.
         * @param isTime True if the number is meant to be parsed as a time, false if the number is just a number.
         * @param _oldPos For performing parsing on a section of a larger string.
         * @return The value of the spoken or word-format number.
         */
        static long double parseNumber(std::string number, const bool& isTime, size_t* _oldPos = nullptr);
        /*!Takes a simple English sentence of a specific form and converts it into a Command object that can be easily read to determine what needs to be executed
         *
         * @authors
         * @brief Takes a simple English sentence and converts it to a Command object
         * @param command A simple English sentence, must be all lowercase.
         * @return A Command struct detailing the desired action and parameters.
         */
        static Command parseCommand(std::string command);
        /*!Converts a DAY_OF_WEEK to an int according to the following: Monday through Sunday is 1 to 7, Tomorrow is 8, and NO_DATE is -1.
         *
         * @authors
         * @brief Converts a DAY_OF_WEEK to an int.
         * @param dow The DAY_OF_WEEK to convert.
         * @return The corresponding int, detailed above.
         */
        static int dowToInt(DAY_OF_WEEK dow);
        /*!
         * An example implementation of the selection blocks to execute the commands done by
         */
        static void executeCommand(const Command& command);
        //static int addCommandTarget(const std::string& target, int numArgs);

        LanguageParser() = delete;

        /*!Driver of the speech recognition capabilities. Adapted from the example shown at https://github.com/julius-speech/julius/blob/master/julius-simple/julius-simple.c
         * Analyses the .wav file found listed in JuliusModel/test.dbl
         *
         * @authors
         * @brief Driver of the speech recognition.
         * @param parsedSpeechOut Pointer to the string where the result is stored.
         * @return 1 if error, 0 otherwise.
         */
//		static int juliusParser(std::string* parsedSpeechOut);

    private:
        static const inline std::vector<std::string> commandTargets{"timer", "reminder", "appointment", "event", "note", "studytimer", "checklist"};
        static std::vector<std::string> customCommandTargets;
        /*!Matches a command target to a
         *
         * @param command
         * @param oldPos
         * @return
         */
        static std::string matchCommandTarget(const std::string& command, size_t* oldPos);
        /*!Macro to check if a word matches any of a list of words that can be skipped.
         *
         * @authors
         * @brief Macro to check if a word matches any of a list of words that can be skipped.
         * @param word The word to check.
         * @return True if the word is on the list of skippable words, false otherwise.
         */
        static inline bool wordMatchesSkippable(const std::string& word);
        /*!Macro to check if a word matches any of the words that begin a preposition phrase that would be a complement to the desired action.
         *
         * @authors
         * @brief Macro to check if a word matches any word that starts a VP Complement.
         * @param word The word to check.
         * @return True if the word is begins a desired preposition phrase, false otherwise.
         */
        static inline bool wordMatchesComplementStart(const std::string& word);
        /*!Takes a word and matches it to the corresponding day of the week, or NO_DATE if not a day of the week.
         *
         * @authors
         * @brief Takes a word and matches it to the corresponding day of the week, or NO_DATE if not a day of the week.
         * @param word The word to check.
         * @return The DAY_OF_WEEK corresponding to the given string.
         */
        static DAY_OF_WEEK wordMatchesDayOfWeek(const std::string& word);

//		static void status_recready(Recog *recog, void *dummy);
//		static void status_recstart(Recog *recog, void *dummy);
//		static void put_hypo_phoneme(WORD_ID *seq, int n, WORD_INFO *winfo);
//		static void output_result(Recog *recog, void *dummy);

};

#endif //COMPSCI3307_PROJECT_LANGUAGEPARSER_H
