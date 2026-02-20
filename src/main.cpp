#include "Manager.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {
	Manager::loadStuff();
	listenForAllSettingChanges([](std::string_view, std::shared_ptr<SettingV3>) {
		Manager::loadStuff();
	});
}