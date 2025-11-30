#include <gtest/gtest.h>
#include "NPC.hpp"
#include "factory.hpp"
#include "dungeon.hpp"
#include "visitor.hpp"
#include "observer.hpp"
#include <memory>
#include <fstream>

// Test fixture для Dungeon
class DungeonTest : public ::testing::Test {
protected:
    void SetUp() override {
        Factory::Init();
    }

    void TearDown() override {
        // Очищаем файлы после тестов
        std::remove("test_dungeon.txt");
        std::remove("test_log.txt");
        std::remove("log.txt");
    }
};

// Тесты для NPC
TEST_F(DungeonTest, NPCCreationAndGetters) {
    auto bear = std::make_unique<Bear>("Baloo", 100.0, 200.0);
    EXPECT_EQ(bear->GetType(), "Bear");
    EXPECT_EQ(bear->GetName(), "Baloo");
    auto pos = bear->GetPos();
    EXPECT_DOUBLE_EQ(pos.first, 100.0);
    EXPECT_DOUBLE_EQ(pos.second, 200.0);

    auto elf = std::make_unique<Elf>("Legolas", 150.0, 250.0);
    EXPECT_EQ(elf->GetType(), "Elf");
    EXPECT_EQ(elf->GetName(), "Legolas");
}

TEST_F(DungeonTest, NPCDistanceCalculation) {
    auto npc1 = std::make_unique<Bear>("Bear1", 0.0, 0.0);
    auto npc2 = std::make_unique<Elf>("Elf1", 3.0, 4.0);
    
    // Расстояние между (0,0) и (3,4) должно быть 5
    EXPECT_DOUBLE_EQ(npc1->Distance(npc2.get()), 5.0);
    
    // Расстояние до себя должно быть 0
    EXPECT_DOUBLE_EQ(npc1->Distance(npc1.get()), 0.0);
    
    // Расстояние до nullptr должно быть 0
    EXPECT_DOUBLE_EQ(npc1->Distance(nullptr), 0.0);
}

TEST_F(DungeonTest, NPCCanAttackLogic) {
    auto bear = std::make_unique<Bear>("Baloo", 0.0, 0.0);
    auto elf = std::make_unique<Elf>("Legolas", 0.0, 0.0);
    auto robber1 = std::make_unique<Robber>("Robin", 0.0, 0.0);
    auto robber2 = std::make_unique<Robber>("John", 0.0, 0.0);
    
    // Медведь атакует эльфа
    EXPECT_TRUE(bear->CanAttack(elf.get()));
    
    // Эльф атакует разбойника
    EXPECT_TRUE(elf->CanAttack(robber1.get()));
    
    // Разбойник атакует разбойника
    EXPECT_TRUE(robber1->CanAttack(robber2.get()));
    
    // Обратные случаи не должны работать
    EXPECT_FALSE(elf->CanAttack(bear.get()));
    EXPECT_FALSE(robber1->CanAttack(elf.get()));
    EXPECT_FALSE(bear->CanAttack(robber1.get()));
    
    // Атака nullptr должна возвращать false
    EXPECT_FALSE(bear->CanAttack(nullptr));
}

TEST_F(DungeonTest, NPCGetMessage) {
    auto bear = std::make_unique<Bear>("Baloo", 0.0, 0.0);
    auto elf = std::make_unique<Elf>("Legolas", 0.0, 0.0);
    
    std::string message = bear->GetMessage(elf.get());
    EXPECT_EQ(message, "Bear Baloo kills Elf Legolas");
    
    // Сообщение для nullptr должно быть пустым
    EXPECT_TRUE(bear->GetMessage(nullptr).empty());
}

TEST_F(DungeonTest, NPCSetPosition) {
    auto npc = std::make_unique<Bear>("TestBear", 10.0, 20.0);
    
    npc->SetPos(30, 40);
    auto pos = npc->GetPos();
    EXPECT_DOUBLE_EQ(pos.first, 30.0);
    EXPECT_DOUBLE_EQ(pos.second, 40.0);
}

// Тесты для Factory
TEST_F(DungeonTest, FactoryCreation) {
    auto bear = Factory::CreateNPC("Bear", "TestBear", 10.0, 20.0);
    ASSERT_NE(bear, nullptr);
    EXPECT_EQ(bear->GetType(), "Bear");
    EXPECT_EQ(bear->GetName(), "TestBear");
    
    auto elf = Factory::CreateNPC("Elf", "TestElf", 30.0, 40.0);
    ASSERT_NE(elf, nullptr);
    EXPECT_EQ(elf->GetType(), "Elf");
    
    auto robber = Factory::CreateNPC("Robber", "TestRobber", 50.0, 60.0);
    ASSERT_NE(robber, nullptr);
    EXPECT_EQ(robber->GetType(), "Robber");
    
    // Неизвестный тип должен возвращать nullptr
    auto unknown = Factory::CreateNPC("Dragon", "TestDragon", 0.0, 0.0);
    EXPECT_EQ(unknown, nullptr);
}

TEST_F(DungeonTest, FactoryCreateFromString) {
    std::string data = "Bear FactoryBear 100.5 200.5";
    auto npc = Factory::CreateNPCFromString(data);
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->GetType(), "Bear");
    EXPECT_EQ(npc->GetName(), "FactoryBear");
    auto pos = npc->GetPos();
    EXPECT_DOUBLE_EQ(pos.first, 100.5);
    EXPECT_DOUBLE_EQ(pos.second, 200.5);
    
    // Неверные данные должны возвращать nullptr
    auto invalid1 = Factory::CreateNPCFromString("Invalid Data");
    EXPECT_EQ(invalid1, nullptr);
    
    auto invalid2 = Factory::CreateNPCFromString("");
    EXPECT_EQ(invalid2, nullptr);
}

// Тесты для Dungeon
TEST_F(DungeonTest, DungeonAddNPC) {
    Dungeon dungeon;
    
    dungeon.AddNPC(Factory::CreateNPC("Bear", "Bear1", 0.0, 0.0));
    dungeon.AddNPC(Factory::CreateNPC("Elf", "Elf1", 10.0, 10.0));
    
    // Добавление nullptr не должно вызывать краш
    dungeon.AddNPC(nullptr);
}

TEST_F(DungeonTest, DungeonSaveAndLoad) {
    Dungeon dungeon;
    
    // Добавляем NPC
    dungeon.AddNPC(Factory::CreateNPC("Bear", "SaveBear", 100.5, 200.5));
    dungeon.AddNPC(Factory::CreateNPC("Elf", "SaveElf", 300.5, 400.5));
    
    // Сохраняем
    dungeon.SaveToFile("test_dungeon.txt");
    
    // Проверяем что файл создался
    std::ifstream check("test_dungeon.txt");
    EXPECT_TRUE(check.is_open());
    check.close();
    
    // Создаем новый dungeon и загружаем
    Dungeon loadedDungeon;
    loadedDungeon.LoadFromFile("test_dungeon.txt");
}

TEST_F(DungeonTest, DungeonLoadNonExistentFile) {
    Dungeon dungeon;
    
    // Загрузка несуществующего файла не должна крашиться
    EXPECT_NO_THROW(dungeon.LoadFromFile("non_existent_file.txt"));
}

// Тесты для Visitor
TEST_F(DungeonTest, VisitorBattleCloseNPCs) {
    Dungeon dungeon;
    
    // Размещаем NPC близко друг к другу
    dungeon.AddNPC(Factory::CreateNPC("Bear", "Bear1", 0.0, 0.0));
    dungeon.AddNPC(Factory::CreateNPC("Elf", "Elf1", 1.0, 1.0)); // Близко
    
    // Запускаем бой с большим радиусом
    dungeon.StartBattle(100.0);
}

TEST_F(DungeonTest, VisitorBattleFarNPCs) {
    Dungeon dungeon;
    
    // Размещаем NPC далеко друг от друга
    dungeon.AddNPC(Factory::CreateNPC("Bear", "Bear1", 0.0, 0.0));
    dungeon.AddNPC(Factory::CreateNPC("Elf", "Elf1", 400.0, 400.0)); // Далеко
    
    // Запускаем бой с маленьким радиусом
    dungeon.StartBattle(10.0);
}

TEST_F(DungeonTest, VisitorRobberBattle) {
    Dungeon dungeon;
    
    // Два разбойника близко
    dungeon.AddNPC(Factory::CreateNPC("Robber", "Robber1", 0.0, 0.0));
    dungeon.AddNPC(Factory::CreateNPC("Robber", "Robber2", 5.0, 5.0));
    
    dungeon.StartBattle(100.0);
}

TEST_F(DungeonTest, VisitorEmptyBattle) {
    Dungeon dungeon;
    
    // Бой без NPC или с одним NPC
    dungeon.StartBattle(100.0);
    
    dungeon.AddNPC(Factory::CreateNPC("Bear", "SoloBear", 0.0, 0.0));
    dungeon.StartBattle(100.0);
}

// Тесты для Observer
class MockObserver : public Observer {
public:
    std::vector<std::string> messages;
    int callCount = 0;
    
    void Update(const std::string& mes) override {
        messages.push_back(mes);
        callCount++;
    }
};

TEST_F(DungeonTest, ObserverPattern) {
    auto mockObserver = std::make_unique<MockObserver>();
    MockObserver* mockPtr = mockObserver.get();
    
    Visitor visitor(100.0);
    visitor.AddObserver(mockPtr);
    
    // Создаем NPC которые будут сражаться
    auto bear = std::make_unique<Bear>("TestBear", 0.0, 0.0);
    auto elf = std::make_unique<Elf>("TestElf", 1.0, 1.0);
    
    // Симулируем визит
    visitor.Visit(bear.get(), elf.get());
    
    // Проверяем что наблюдатель получил сообщение
    EXPECT_GT(mockPtr->callCount, 0);
    ASSERT_FALSE(mockPtr->messages.empty());
    EXPECT_EQ(mockPtr->messages[0], "Bear TestBear kills Elf TestElf");
}

TEST_F(DungeonTest, ObserverAddRemove) {
    Visitor visitor(100.0);
    
    auto observer1 = std::make_unique<MockObserver>();
    auto observer2 = std::make_unique<MockObserver>();
    
    MockObserver* ptr1 = observer1.get();
    MockObserver* ptr2 = observer2.get();
    
    visitor.AddObserver(ptr1);
    visitor.AddObserver(ptr2);
    visitor.AddObserver(nullptr); // nullptr не должен добавляться
    
    // Удаляем observer
    visitor.RemoveObserver(ptr1);
    
    // Проверяем что удаление работает
    auto bear = std::make_unique<Bear>("Test", 0.0, 0.0);
    auto elf = std::make_unique<Elf>("Test", 1.0, 1.0);
    
    visitor.Visit(bear.get(), elf.get());
    
    // Только второй observer должен получить сообщение
    EXPECT_EQ(ptr1->callCount, 0); // Удален - не получил
    EXPECT_GT(ptr2->callCount, 0); // Оставлен - получил
}

// Тесты граничных случаев
TEST_F(DungeonTest, NullptrSafety) {
    // Все методы должны безопасно обрабатывать nullptr
    auto npc = std::make_unique<Bear>("Test", 0.0, 0.0);
    
    EXPECT_NO_THROW(npc->CanAttack(nullptr));
    EXPECT_NO_THROW(npc->Distance(nullptr));
    EXPECT_NO_THROW(npc->GetMessage(nullptr));
    
    Visitor visitor(100.0);
    EXPECT_NO_THROW(visitor.Visit(nullptr, nullptr));
    EXPECT_NO_THROW(visitor.Visit(npc.get(), nullptr));
    EXPECT_NO_THROW(visitor.Visit(nullptr, npc.get()));
}

TEST_F(DungeonTest, CoordinateBoundaries) {
    // Тестируем граничные значения координат
    auto npc = std::make_unique<Bear>("BoundaryTest", 0.0, 500.0);
    auto pos = npc->GetPos();
    
    EXPECT_GE(pos.first, 0.0);
    EXPECT_GE(pos.second, 0.0);
    EXPECT_LE(pos.first, 500.0);
    EXPECT_LE(pos.second, 500.0);
    
    // Меняем позицию
    npc->SetPos(500, 0);
    pos = npc->GetPos();
    EXPECT_DOUBLE_EQ(pos.first, 500.0);
    EXPECT_DOUBLE_EQ(pos.second, 0.0);
}

// Интеграционный тест
TEST_F(DungeonTest, IntegrationTest) {
    Dungeon dungeon;
    
    // Создаем разнообразных NPC
    dungeon.AddNPC(Factory::CreateNPC("Bear", "BigBear", 50.0, 50.0));
    dungeon.AddNPC(Factory::CreateNPC("Elf", "FastElf", 60.0, 60.0)); 
    dungeon.AddNPC(Factory::CreateNPC("Robber", "SneakyRobber", 70.0, 70.0));
    dungeon.AddNPC(Factory::CreateNPC("Robber", "AnotherRobber", 80.0, 80.0));
    
    // Сохраняем состояние
    dungeon.SaveToFile("integration_test.txt");
    
    // Проводим бой
    dungeon.StartBattle(50.0);
    
    // Загружаем сохраненное состояние
    Dungeon loadedDungeon;
    loadedDungeon.LoadFromFile("integration_test.txt");
}

// Тест файлового наблюдателя
TEST_F(DungeonTest, FileObserverTest) {
    // Удаляем старый лог файл если есть
    std::remove("test_log.txt");
    
    {
        FileObserver fileObserver;
        fileObserver.Update("Test message 1");
        fileObserver.Update("Test message 2");
    } // FileObserver уничтожается здесь, файл закрывается
    
    // Проверяем что файл создался и содержит сообщения
    std::ifstream logFile("log.txt");
    EXPECT_TRUE(logFile.is_open());
    
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(logFile, line)) {
        lines.push_back(line);
    }
    
    // Должны быть наши сообщения
    EXPECT_GE(lines.size(), 2);
}

// Тест консольного наблюдателя
TEST_F(DungeonTest, ConsoleObserverTest) {
    ConsoleObserver consoleObserver;
    
    // Не должно быть исключений
    EXPECT_NO_THROW(consoleObserver.Update("Test console message"));
}

// Тест всех NPC типов
TEST_F(DungeonTest, AllNPCTypeCombinations) {
    auto bear = Factory::CreateNPC("Bear", "B", 0.0, 0.0);
    auto elf = Factory::CreateNPC("Elf", "E", 1.0, 1.0);
    auto robber = Factory::CreateNPC("Robber", "R", 2.0, 2.0);
    
    ASSERT_NE(bear, nullptr);
    ASSERT_NE(elf, nullptr);
    ASSERT_NE(robber, nullptr);
    
    // Проверяем все комбинации CanAttack
    EXPECT_TRUE(bear->CanAttack(elf.get()));
    EXPECT_FALSE(bear->CanAttack(robber.get()));
    
    EXPECT_TRUE(elf->CanAttack(robber.get()));
    EXPECT_FALSE(elf->CanAttack(bear.get()));
    
    EXPECT_TRUE(robber->CanAttack(robber.get()));
    EXPECT_FALSE(robber->CanAttack(bear.get()));
    EXPECT_FALSE(robber->CanAttack(elf.get()));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}