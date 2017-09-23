#include <string>
#include <iostream>
#include <vector>

struct MadLibChunk
{	
	std::string before;
	std::string prompt;	
	std::string userInput;

	void GetUserInput()
	{
		std::cout << prompt;
		std::getline(std::cin, userInput);		
	}

	void Display() const
	{
		std::cout << before << userInput;
	}
};

class MadLib
{
public:

	MadLib(const std::string& str)
	{		
		int iAt = 0;
		while (iAt < str.length() && iAt >= 0)
		{
			MadLibChunk chunk;

			int next = str.find('{', iAt);
			chunk.before = str.substr(iAt, next - iAt);

			if (next == -1)
			{
				break;
			}

			int close = str.find('}', next);
			chunk.prompt = str.substr(next + 1, close - next - 1) + ": ";

			ChunkList.push_back(chunk);
			iAt = close + 1;
		}

		FinalText = str.substr(iAt);
	}

	void PromptUser()
	{
		for (auto& e : ChunkList)
		{
			e.GetUserInput();
		}
	}

	void DisplayStory()
	{
		for (const auto& e : ChunkList)
		{
			e.Display();
		}

		std::cout << FinalText << "\n";
	}

private:
	std::vector<MadLibChunk> ChunkList;
	std::string FinalText;
};



int main()
{
	std::string story = "\
I spent last summer on my grandfather's {adjective} farm.  He raises {noun/s} for local food {noun/s}.  He also grows \
corn on the {noun}, {adjective} lettuce, and lima {noun/s}.  My favorite place to {verb} on the farm is the {adjective} house where \
grandfather keeps his {noun/s}.  But when I visit in November, there are no {noun/s}!  They are all gone!  I anxiously await at the table \
that Thanksgiving.  I am relived when Grandma brings out the {noun} for Thanksgiving dinner.";

	MadLib m(story);
	m.PromptUser();
	m.DisplayStory();

	system("pause");
    return 0;
}

