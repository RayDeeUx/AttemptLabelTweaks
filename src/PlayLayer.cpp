#include <Geode/modify/PlayLayer.hpp>
#include "Manager.hpp"

using namespace geode::prelude;

#define HIDE_IN_NORMAL_MODE GameManager::get()->getGameVariable("0134")
#define HIDE_IN_PRCTCE_MODE GameManager::get()->getGameVariable("0135")
#define CHROMA_ACTION_TAG 5142025

#define GET_MANAGER\
	Manager* manager = Manager::getSharedInstance();\
	if (!manager->enabled) return;

#define ABORT_IF_NO_LABEL\
	CCLabelBMFont* theLabelItself = m_fields->theLabelItself;\
	if (!theLabelItself) return;

#define LOG_VARIABLES(isPracticeMode, conditionWithPracticeMode, shouldEnableBecausePractice, isTestMode, conditionWithTestmode, shouldEnableBecauseTestmode, conditionWithoutTestmode, shouldEnableBecauseNormal)\
	log::info("————— PRACTICE MODE VARIABLES —————");\
	log::info("m_isPracticeMode: {}", isPracticeMode);\
	log::info("conditionWithPracticeMode: {}", conditionWithPracticeMode);\
	log::info("shouldEnableBecausePractice: {}", shouldEnableBecausePractice);\
	log::info("————— TESTMODE VARIABLES —————");\
	log::info("m_isTestMode: {}", isTestMode);\
	log::info("conditionWithTestmode: {}", conditionWithTestmode);\
	log::info("shouldEnableBecauseTestmode: {}", shouldEnableBecauseTestmode);\
	log::info("————— NORMAL MODE VARIABLES —————");\
	log::info("!m_isTestMode && !m_isPracticeMode: {}", !m_isTestMode && !m_isPracticeMode);\
	log::info("conditionWithoutTestmode: {}", conditionWithoutTestmode);\
	log::info("shouldEnableBecauseNormal: {}", shouldEnableBecauseNormal);\
	log::info("————— END PRINTING VARIABLES —————");

#define LOG_OPTIONS(optionForNormal, optionForPractice, optionForTestmode)\
	log::info("————— PRACTICE MODE OPTIONS —————");\
	log::info("shouldEnableBecausePractice: {}", shouldEnableBecausePractice);\
	log::info("optionForPractice: {}", optionForPractice);\
	log::info("————— TESTMODE OPTIONS —————");\
	log::info("shouldEnableBecauseTestmode: {}", shouldEnableBecauseTestmode);\
	log::info("optionForTestmode: {}", optionForTestmode);\
	log::info("————— NORMAL MODE OPTIONS —————");\
	log::info("shouldEnableBecauseNormal: {}", shouldEnableBecauseNormal);\
	log::info("optionForNormal: {}", optionForNormal);\
	log::info("————— END PRINTING OPTIONS —————");

#define EARLY_RETURN(conditionWithoutTestmode, conditionWithPracticeMode, conditionWithTestmode)\
	const bool shouldEnableBecauseTestmode = m_isTestMode && conditionWithTestmode;\
	const bool shouldEnableBecausePractice = m_isPracticeMode && conditionWithPracticeMode;\
	const bool shouldEnableBecauseNormal = !m_isTestMode && !m_isPracticeMode && conditionWithoutTestmode;\
	LOG_VARIABLES(m_isPracticeMode, conditionWithPracticeMode, shouldEnableBecausePractice, m_isTestMode, conditionWithTestmode, shouldEnableBecauseTestmode, conditionWithoutTestmode, shouldEnableBecauseNormal)\
	if (!shouldEnableBecauseTestmode && !shouldEnableBecausePractice && !shouldEnableBecauseNormal) {\
		Fields* fields = m_fields.self();\
		if (fields->theLabelItself) fields->theLabelItself->stopActionByTag(CHROMA_ACTION_TAG);\
		return log::info("Nothing was chosen. Everything is false, so this is fine. (Probably?)");\
	}

#define SELECT_OPTION_USING(shouldEnableBecauseNormal, shouldEnableBecausePractice, shouldEnableBecauseTestmode, memory, type, optionForNormal, optionForPractice, optionForTestmode)\
	LOG_OPTIONS(optionForNormal, optionForPractice, optionForTestmode)\
	type memory;\
	if (shouldEnableBecausePractice) memory = optionForPractice;\
	else if (shouldEnableBecauseTestmode) memory = optionForTestmode;\
	else if (shouldEnableBecauseNormal) memory = optionForNormal;\
	else {\
		Fields* fields = m_fields.self();\
		if (fields->theLabelItself) fields->theLabelItself->stopActionByTag(CHROMA_ACTION_TAG);\
		return log::info("Nothing was chosen. Something went wrong...");\
	}

#define SETUP_THE_LABEL_ITSELF_USING(conditionWithoutTestmode, conditionWithPracticeMode, conditionWithTestmode, memory, type, optionForNormal, optionForPractice, optionForTestmode)\
	GET_MANAGER\
	EARLY_RETURN(conditionWithoutTestmode, conditionWithPracticeMode, conditionWithTestmode)\
	SELECT_OPTION_USING(shouldEnableBecauseNormal, shouldEnableBecausePractice, shouldEnableBecauseTestmode, memory, type, optionForNormal, optionForPractice, optionForTestmode)\
	ABORT_IF_NO_LABEL

#define PASSIVELY_REPLACE_ATTEMPT_LABEL\
	if (!m_attemptLabel || !theLabelItself) return;\
	m_attemptLabel->setScaleX(0.f);\
	m_attemptLabel->setScaleY(0.f);\
	theLabelItself->setZOrder(m_attemptLabel->getZOrder());\
	theLabelItself->setVisible(m_attemptLabel->isVisible());\
	theLabelItself->setPosition(m_attemptLabel->getPosition());

#define CUSTOMIZE_THE_LABEL_ITSELF\
	ABORT_IF_NO_LABEL\
	PASSIVELY_REPLACE_ATTEMPT_LABEL\
	theLabelItself->setScaleX(1.f);\
	theLabelItself->setScaleY(1.f);\
	theLabelItself->setString(m_attemptLabel->getString());\
	theLabelItself->setBlendFunc({ GL_ONE, GL_ONE_MINUS_SRC_ALPHA });\
	theLabelItself->setFntFile("bigFont.fnt");\
	theLabelItself->setColor({255, 255, 255});\
	theLabelItself->setOpacity(255);\
	MyPlayLayer::setFont();\
	MyPlayLayer::setScale();\
	MyPlayLayer::setAlpha();\
	MyPlayLayer::setColor();\
	MyPlayLayer::setChrma();\
	MyPlayLayer::setLabel();\

class $modify(MyPlayLayer, PlayLayer) {
	struct Fields {
		CCLabelBMFont* theLabelItself = nullptr;
	};
	/*
	void postUpdate(float dt) {
		// fuck you shstaalrgw
		PlayLayer::postUpdate(dt);
		if (!m_attemptLabel) return;
		auto fields = m_fields.self();
		if (!fields || !fields->theLabelItself) return;
		fields->theLabelItself->setPosition(m_attemptLabel->getPosition());
	}
	*/
	void setFont() {
		SETUP_THE_LABEL_ITSELF_USING(manager->cFontB, manager->cFontP, manager->cFontT, fontID, int, manager->font, manager->fontPractice, manager->fontTestmode)
		switch (fontID) {
			case -3: theLabelItself->setFntFile("chatFont.fnt"); break;
			case -2: theLabelItself->setFntFile("goldFont.fnt"); break;
			case -1: theLabelItself->setFntFile("bigFont.fnt"); break;
			case  0: theLabelItself->setFntFile(m_attemptLabel->getFntFile()); break;
			default: theLabelItself->setFntFile(fmt::format("gjFont{:02d}.fnt", fontID).c_str()); break;
		}
		if (fontID == -3 && manager->blend) theLabelItself->setBlendFunc({ GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA });
	}
	void setAlpha() {
		SETUP_THE_LABEL_ITSELF_USING(manager->alphaB, manager->alphaP, manager->alphaT, alpha, int, manager->alpha, manager->alphaPractice, manager->alphaTestmode)
		theLabelItself->setOpacity(alpha);
	}
	void setColor() {
		SETUP_THE_LABEL_ITSELF_USING(manager->colorB, manager->colorP, manager->colorT, color, ccColor3B, manager->color, manager->colorPractice, manager->colorTestmode)
		theLabelItself->setColor(color);
	}
	void setScale() {
		SETUP_THE_LABEL_ITSELF_USING(manager->scaleB, manager->scaleP, manager->scaleT, scale, float, manager->scale, manager->scalePractice, manager->scaleTestmode)
		theLabelItself->setScale(scale);
	}
	void setChrma() {
		Fields* fields = m_fields.self();
		if (fields->theLabelItself) fields->theLabelItself->stopActionByTag(CHROMA_ACTION_TAG);
		SETUP_THE_LABEL_ITSELF_USING(manager->chroma, manager->chromP, manager->chromT, speed, float, manager->chromaSpeed, manager->chromaSpeedPractice, manager->chromaSpeedTestmode)
		CCTintTo* tintOne = CCTintTo::create(speed, 255, 128, 128);
		CCTintTo* tintTwo = CCTintTo::create(speed, 255, 255, 128);
		CCTintTo* tintThree = CCTintTo::create(speed, 128, 255, 128);
		CCTintTo* tintFour = CCTintTo::create(speed, 128, 255, 255);
		CCTintTo* tintFive = CCTintTo::create(speed, 128, 128, 255);
		CCTintTo* tintSix = CCTintTo::create(speed, 255, 128, 255);
		CCSequence* sequence = CCSequence::create(tintOne, tintTwo, tintThree, tintFour, tintFive, tintSix, nullptr);
		CCRepeat* repeat = CCRepeat::create(sequence, 3999);
		repeat->setTag(CHROMA_ACTION_TAG);
		theLabelItself->runAction(repeat);
	}
	void setLabel() {
		SETUP_THE_LABEL_ITSELF_USING(manager->format, manager->formaP, manager->formTT, prefix, std::string, manager->attemptPrefix, manager->attemptPrefixPractice, manager->attemptPrefixTestmode)
		SELECT_OPTION_USING(shouldEnableBecauseNormal, shouldEnableBecausePractice, shouldEnableBecauseTestmode, suffix, std::string, manager->attemptSuffix, manager->attemptSuffixPractice, manager->attemptSuffixTestmode)
		SELECT_OPTION_USING(shouldEnableBecauseNormal, shouldEnableBecausePractice, shouldEnableBecauseTestmode, useTotalAttempts, bool, manager->atempt, manager->attemP, manager->attmTT)
		const int attemptsForLabel = useTotalAttempts ? m_level->m_attempts.value() : m_attempts;
		const std::string& formatForLabel = geode::utils::string::trim(fmt::format("{} {} {}", prefix, attemptsForLabel, suffix));
		theLabelItself->setString(formatForLabel.c_str());
	}
	void setupHasCompleted() {
		PlayLayer::setupHasCompleted();
		if (!m_attemptLabel || !m_attemptLabel->getParent()) return;

		CCLabelBMFont* theLabelItself = CCLabelBMFont::create(m_attemptLabel->getString(), "bigFont.fnt");
		m_fields->theLabelItself = theLabelItself;

		m_attemptLabel->getParent()->addChild(theLabelItself);
		PASSIVELY_REPLACE_ATTEMPT_LABEL

		theLabelItself->setID("custom-attempt-label"_spr);

		MyPlayLayer::setFont();
		MyPlayLayer::setScale();
		MyPlayLayer::setAlpha();
		MyPlayLayer::setColor();
		MyPlayLayer::setChrma();
		MyPlayLayer::setLabel();
	}
	void resetLevel() {
		PlayLayer::resetLevel();
		if (!m_attemptLabel) return;
		CUSTOMIZE_THE_LABEL_ITSELF
	}
	void togglePracticeMode(bool isPractice) {
		PlayLayer::togglePracticeMode(isPractice);
		if (!m_attemptLabel) return;
		CUSTOMIZE_THE_LABEL_ITSELF
	}
	void startMusic() {
		// fuck you shstaalrgw
		PlayLayer::startMusic();
		if (!m_attemptLabel) return;
		auto fields = m_fields.self();
		if (!fields || !fields->theLabelItself) return;
		fields->theLabelItself->setPosition(m_attemptLabel->getPosition());
	}
};
