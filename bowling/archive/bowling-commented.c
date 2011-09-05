#include <stdio.h>

// This function calculates the absolute score (i.e. no. of pins knocked down) for the specified throw of the ball.
// As an added optimization for this logic, we assume that numScore > 0 (Note that its easier to calculate the score for the first throw - which cannot be a spare).
// We use inline, because the function itself is quite small, and we can avoid the function call overhead (especially from within the program's inner while loop).
// Note that the use of -O3 in the Makefile will force g++/gcc to perform inlining.
inline unsigned int getScore(const char* charBuffer, const unsigned int* scores, unsigned int numScore)
{
	// The characters denoting scores are space separated. So for a specified numScore, the character in play is actually at index (numScore * 2).
	// Note: We trust the compiler to optimize the *2 operation into a bit-shift operation.
	unsigned int result = charBuffer[numScore * 2];

	// Even though statistically, we are more likely to encounter a digit than 'X' or '/',
	// since the digits lie in the middle of the range of expected characters,
	// we would need at least 2 comparisons to determine whether a character is a digit.
	// To make each comparison count, we use the following sequence of 'if' conditions.
	// Additionally, we use the gnu extention __builtin_expect, to help with CPU branch prediction.

	if (__builtin_expect(result == 'X', 0)) return 10U;								// Handle a 'Strike'.
	if (__builtin_expect(result == '/', 0)) return (10U - scores[numScore - 1]);	// Handle a 'Spare' by looking at the previous score.
	return (result - '0');															// Handle a digit.
}

int main(int argc, char**argv)
{
	// Variables to manage file reading.
	FILE* fp = fopen(argv[1],"r");
	char charBuffer[64], *ptrToBuffer = charBuffer;
	size_t bufferSize = 64U;

	// We use bufferred IO to fetch complete lines at a time into a pre-allocated buffer.
	// We assume that the standard library can use optimized routines to detect the EOL.
	// Line processing allows us to simplify further logic...
	while (getline(&ptrToBuffer, &bufferSize, fp) != -1)
	{
		// Buffer to hold scores for each throw of the ball (max required would be 10 frames * 2 max throws = 20, + up to 2 bonus throws for the final frame.
		unsigned int scores[22];
		// Suggest to the compiler to use registers for the following counter-like variables.
		register unsigned int totalScore = 0, numCompletedFrames = 0, isFrameAboutToComplete = 0, i = 0;

		// According to the rules for calculating bowling scores,
		// for each throw of the ball, certain scores affect/depend on future scores (at most 2 throws ahead).
		// Here we pre-fetch the scores for the first 2 throws, and in the main loop,
		// we analyze the impact of the current score AFTER fetching the score for a throw 2 steps in the future.
		// In this way, at each step, we have enough information to calculate the COMPLETE score due to the current throw,
		// while we iterate through all the scores ONLY once.
		scores[0] = (charBuffer[0] == 'X') ? 10U : (charBuffer[0] - '0');	// A spare - '/' is not possible at this stage, so we avoid the slightly more complex logic used in getScore().
		scores[1] = getScore(charBuffer, scores, 1);

		// This while loop checks on the number of frames whose scores have been completely analyzed (rather than the number of characters in a line).
		while (numCompletedFrames < 10U)
		{
			scores[i+2] = getScore(charBuffer, scores, i+2);	// Fetch a score that 2 steps ahead.
			totalScore += scores[i];							// Account for the minimum contribution to the totalScore for this throw.

			if (isFrameAboutToComplete)							// Handle the case when we are analyzing the 2nd score for a frame.
			{
				if (__builtin_expect(((scores[i-1] + scores[i]) == 10U), 0))	// Check if this 2nd throw resulted in a statistically unlikely 'Spare'.
				{
					totalScore += scores[i+1];					// If yes, we also account for the next score in the totalScore.
				}

				++numCompletedFrames;
				isFrameAboutToComplete = 0;
			}
			// From this point onwards we are analyzing the score for the 1st throw for a frame.
			else if (__builtin_expect((scores[i] == 10U), 0))	// Check if the first throw for a frame resulted in a statistically unlikely 'Strike'.
			{
				totalScore += scores[i+1] + scores[i+2];		// If yes, we also account for the next 2 scores in the totalScore.
				++numCompletedFrames;
			}
			else												// Else, since we cannot have a 'Spare' at this stage, its a regular score.
			{
				isFrameAboutToComplete = 1;						// Set a flag to indicate that the next score will indicate the end of the current frame.
			}

			++i;												// Increment the index counter so that the next score is analyzed in the next iteration.
		}

		printf("%d\n", totalScore);								// Print the final score for the current game.
	}
	fflush(stdout);
	_exit(0);
}
