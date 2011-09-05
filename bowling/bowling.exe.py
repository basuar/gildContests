#!/usr/bin/python
import sys

def getScore(scores, numScore):
	if scores[numScore] == 'X':
		scores[numScore] = int(10)
	elif scores[numScore] == '/':
		scores[numScore] = 10 - int(scores[numScore - 1])
	else:
		scores[numScore] = int(scores[numScore])

f = open(sys.argv[1], 'r')
for line in f:
	scores = line.split()

	totalScore = 0
	numCompletedFrames = 0
	isFrameAboutToComplete = 0
	i = 0

	getScore(scores, 0)
	getScore(scores, 1)

	while numCompletedFrames < 10:
		if i+2 < len(scores):
			getScore(scores, i+2)
		totalScore += (scores[i])

		if isFrameAboutToComplete == 1:
			if ((scores[i-1]) + (scores[i])) == 10:
				totalScore += (scores[i+1])
			numCompletedFrames += 1
			isFrameAboutToComplete = 0
		elif scores[i] == 10:
			totalScore += (scores[i+1]) + (scores[i+2])
			numCompletedFrames += 1
		else:
			isFrameAboutToComplete = 1

		i += 1

	print totalScore
