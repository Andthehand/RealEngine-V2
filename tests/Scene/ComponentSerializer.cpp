#include <gtest/gtest.h>

#include <ryml.hpp>

#include "RealEngine.h"
#include "RealEngine/Scene/ComponentSerializer.h"

template<typename T>
void TestSerializeComponent() {
	T serializeComponent;
	ryml::Tree tree;
	ryml::NodeRef node = tree.rootref();
	node |= ryml::MAP;

	RealEngine::ComponentSerializer<T>::Serialize(node, serializeComponent);

	T deserializeComponent;
	RealEngine::ComponentSerializer<T>::Deserialize(node, &deserializeComponent);

	EXPECT_EQ(serializeComponent, deserializeComponent) << "Serialization and deserialization of component " << typeid(T).name() << " failed.";
}

template<typename... Components>
void TestSerializeComponents(RealEngine::ComponentList::ComponentGroup<Components...>) {
	((TestSerializeComponent<Components>()), ...);
}

TEST(ComponentSerializer, ComponentSerializer_BasicTest) {
	TestSerializeComponents(RealEngine::ComponentList::GetAllComponents());
}
