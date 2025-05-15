#pragma once

// macro adapted from user95401
#define GET_SETTING(type, key) Mod::get()->getSettingValue<type>(key)
#define SET_MANAGER(memory, type, key) memory = GET_SETTING(type, key)

// Manager.hpp structure by acaruso
// reused with explicit permission and strong encouragement

using namespace geode::prelude;

class Manager {

protected:
	static Manager* instance;
public:

	bool enabled = false;
	bool logging = false;
	bool blend = false;

	bool format = false;
	bool formaP = false;
	bool formTT = false;

	bool colorB = false;
	bool colorP = false;
	bool colorT = false;

	bool alphaB = false;
	bool alphaP = false;
	bool alphaT = false;

	bool chroma = false;
	bool chromP = false;
	bool chromT = false;

	bool scaleB = false;
	bool scaleP = false;
	bool scaleT = false;

	bool cFontB = false;
	bool cFontP = false;
	bool cFontT = false;

	bool atempt = false;
	bool attemP = false;
	bool attmTT = false;

	int font = 0;
	int fontPractice = 0;
	int fontTestmode = 0;

	int alpha = 0;
	int alphaPractice = 0;
	int alphaTestmode = 0;

	ccColor3B color = {255, 255, 255};
	ccColor3B colorPractice = {255, 255, 255};
	ccColor3B colorTestmode = {255, 255, 255};

	float scale = .0f;
	float scalePractice = .0f;
	float scaleTestmode = .0f;

	float chromaSpeed = .0f;
	float chromaSpeedPractice = .0f;
	float chromaSpeedTestmode = .0f;

	std::string attemptPrefix;
	std::string attemptPrefixTestmode;
	std::string attemptPrefixPractice;

	std::string attemptSuffix;
	std::string attemptSuffixTestmode;
	std::string attemptSuffixPractice;

	CCLabelBMFont* theLabelItself = nullptr;
	CCRepeatForever* chromaAction = nullptr;

	static Manager* getSharedInstance() {
		if (!instance) instance = new Manager();
		return instance;
	}

	static void loadStuff() {
		if (!instance) instance = new Manager();

		SET_MANAGER(instance->enabled, bool, "enabled");
		SET_MANAGER(instance->logging, bool, "logging");
		SET_MANAGER(instance->blend, bool, "blend");

		SET_MANAGER(instance->format, bool, "format");
		SET_MANAGER(instance->formaP, bool, "formaP");
		SET_MANAGER(instance->formTT, bool, "formTT");

		SET_MANAGER(instance->colorB, bool, "colorB");
		SET_MANAGER(instance->colorP, bool, "colorP");
		SET_MANAGER(instance->colorT, bool, "colorT");

		SET_MANAGER(instance->alphaB, bool, "alphaB");
		SET_MANAGER(instance->alphaP, bool, "alphaP");
		SET_MANAGER(instance->alphaT, bool, "alphaT");

		SET_MANAGER(instance->chroma, bool, "chroma");
		SET_MANAGER(instance->chromP, bool, "chromP");
		SET_MANAGER(instance->chromT, bool, "chromT");

		SET_MANAGER(instance->scaleB, bool, "scaleB");
		SET_MANAGER(instance->scaleP, bool, "scaleP");
		SET_MANAGER(instance->scaleT, bool, "scaleT");

		SET_MANAGER(instance->cFontB, bool, "cFontB");
		SET_MANAGER(instance->cFontP, bool, "cFontP");
		SET_MANAGER(instance->cFontT, bool, "cFontT");

		SET_MANAGER(instance->atempt, bool, "atempt");
		SET_MANAGER(instance->attemP, bool, "attemP");
		SET_MANAGER(instance->attmTT, bool, "attmTT");

		SET_MANAGER(instance->font, int64_t, "font");
		SET_MANAGER(instance->fontPractice, int64_t, "fontPractice");
		SET_MANAGER(instance->fontTestmode, int64_t, "fontTestmode");

		SET_MANAGER(instance->alpha, int64_t, "alpha");
		SET_MANAGER(instance->alphaPractice, int64_t, "alphaPractice");
		SET_MANAGER(instance->alphaTestmode, int64_t, "alphaTestmode");

		SET_MANAGER(instance->scale, float, "scale");
		SET_MANAGER(instance->scalePractice, float, "scalePractice");
		SET_MANAGER(instance->scaleTestmode, float, "scaleTestmode");

		SET_MANAGER(instance->chromaSpeed, float, "chromaSpeed");
		SET_MANAGER(instance->chromaSpeedPractice, float, "chromaSpeedPractice");
		SET_MANAGER(instance->chromaSpeedTestmode, float, "chromaSpeedTestmode");

		SET_MANAGER(instance->color, ccColor3B, "color");
		SET_MANAGER(instance->colorPractice, ccColor3B, "colorPractice");
		SET_MANAGER(instance->colorTestmode, ccColor3B, "colorTestmode");

		SET_MANAGER(instance->attemptPrefix, std::string, "attemptPrefix");
		SET_MANAGER(instance->attemptPrefixPractice, std::string, "attemptPrefixPractice");
		SET_MANAGER(instance->attemptPrefixTestmode, std::string, "attemptPrefixTestmode");

		SET_MANAGER(instance->attemptSuffix, std::string, "attemptSuffix");
		SET_MANAGER(instance->attemptSuffixPractice, std::string, "attemptSuffixPractice");
		SET_MANAGER(instance->attemptSuffixTestmode, std::string, "attemptSuffixTestmode");

		Mod::get()->setLoggingEnabled(instance->logging);
	}

};