#include "Manager.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {
	Manager::loadStuff();
	listenForAllSettingChanges([](std::shared_ptr<SettingV3> _) {
		Manager::loadStuff();
	});
}