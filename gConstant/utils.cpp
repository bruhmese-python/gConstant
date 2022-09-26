#include "utils.h"
#include "sceneManager.h"

size_t count = 0;

template <typename... S1>
auto utils::helperSum(S1... s)
{
	return (s + ...);
}

double utils::distance(position a, position b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int utils::randInRange(int min, int max)
{
	return min + (std::rand() % (max - min + 1));
}

void utils::println(std::string text)
{
	if (count >= 50)
	{
		sceneManager::text->setText(L"");
		count = 0;
	}

	std::wstring ptext(sceneManager::text->getText());
	std::string sptext(ptext.begin(), ptext.end());
	std::string s = sptext + "\n" + text;
	std::wstring ws(s.begin(), s.end());
	sceneManager::text->setText(ws.c_str());

	count++;
}