scores = {}
function split(str, delimiter)
  scores = {};local from = 1;local delim_from, delim_to = string.find( str, delimiter, from )
  while delim_from do scores[#scores+1] = string.sub( str, from , delim_from-1 );from = delim_to + 1;delim_from, delim_to = string.find( str, delimiter, from ); end
  scores[#scores+1] = string.sub( str, from )
end
function getScore(numScore) if scores[numScore] == 'X' then scores[numScore] = 10 else if scores[numScore] == '/' then scores[numScore] = 10 - scores[numScore - 1] end end end
for line in io.lines(arg[1]) do
	split(line, " "); local totalScore = 0; local numCompletedFrames = 0; local isFrameAboutToComplete = 0; local i = 1; getScore(1);getScore(2);
	while numCompletedFrames < 10 do
		if i+2 <= #scores then getScore(i+2) end
		totalScore = totalScore + scores[i];
		if isFrameAboutToComplete == 1 then
			if ((scores[i-1]) + (scores[i])) == 10 then totalScore = totalScore + scores[i+1] end
			numCompletedFrames = numCompletedFrames + 1; isFrameAboutToComplete = 0;
		else if scores[i] == 10 then totalScore = totalScore + scores[i+1] + scores[i+2]; numCompletedFrames = numCompletedFrames + 1; else isFrameAboutToComplete = 1; end end
		i = i + 1
	end
	print(totalScore)
end

