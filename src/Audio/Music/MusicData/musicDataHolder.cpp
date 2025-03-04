#include "musicDataHolder.hpp"

#include "Logs/logs.hpp"
#include "Utilities/xml.hpp"

namespace ph{

MusicDataHolder::MusicDataHolder()
{
	Xml musicDataXml;
	musicDataXml.loadFromFile("music/musicData.xml");
	const Xml musicDataNode = musicDataXml.getChild("musicdata");
	const std::vector<Xml> themeNodes = musicDataNode.getChildren("theme");
	for(const auto& themeNode : themeNodes) {
		const std::string fileName = themeNode.getAttribute("filename").toString();
		const std::string filePath = "music/" + fileName;
		const float volumeMultiplier = themeNode.getAttribute("volumemultiplier").toFloat();
		const bool loop = themeNode.getAttribute("loop").toBool();
		mAllThemesData[filePath] = MusicData(volumeMultiplier, loop);
	}
}

auto MusicDataHolder::getMusicData(const std::string& filePath) -> const MusicData&
{
	auto found = mAllThemesData.find(filePath);
	if (found == mAllThemesData.end())
		PH_EXCEPTION("MusicData with filepath \"" + filePath + "\" was not found.");
	mCurrentThemeData = found->second;
	return found->second;
}

}