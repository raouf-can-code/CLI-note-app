#include <iostream>
#include <vector>
// #include <fstream>
// #include "json.hpp"
#include "../Headers/utils.hpp"

using str = std::string;

class Note {
public:
  str title;
  str description;

  Note(str t, str des) {
    this->title = t;
    this->description = des;
  }

  void edit(str newTi, str newDes) {
    if (!newTi.empty()) {
      this->title = newTi;
    }
    if (!newDes.empty()) {
      this->description = newDes;
    }
  }
};

// functions declaration:
void displayNotes(std::vector<Note> &arr);
void removeNote(std::vector<Note> &vec, int index);
void switchPos(std::vector<Note> &arr, int index, int targetIndex);
void changePos(std::vector<Note> &arr, int index, int targetIndex);

// main Funcstion
int main(int argc, char *argv[]) {
  str data = "notes.json";
  nlohmann::json jsonNotes = json::getJson(data);
  std::vector<Note> notes;

  if (!json::isFileEmpty(data)) {
    for (const auto &item : jsonNotes) {
      notes.emplace_back(item.value("title", ""),
                         item.value("description", ""));
    }
  }
  bool on = true;
  int index, target, opt;

  std::cout << "------ Notes ------\n";
  std::cout << "welcome to Notes\n";

  do {
    std::cout << "press enter to show options ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\n options: \n 1.List the notes \n 2.Add a note\n 3.Remove a "
                 "note\n 4.Edit a note\n 5.Switch places\n 6.Change position\n "
                 "7.Exit \n Enter your option: ";
    std::cin >> opt;
    std::cin.ignore();

    switch (opt) {
    case 1: // diplay notes
      displayNotes(notes);
      break;

    case 2: { /* add note */
      std::string inputTitle, inputDescription;
      std::cout << "Enter the Title: ";
      std::getline(std::cin, inputTitle);
      std::cout << "Enter a description about your note: ";
      std::getline(std::cin, inputDescription);
      notes.emplace_back(inputTitle, inputDescription);
      break;
    }

    case 3: { /* remove note */
      int index;
      std::cout << "Enter the index of the note to remove: ";
      std::cin >> index;
      std::cin.ignore();
      removeNote(notes, index);
      break;
    }

    case 4: { /* edit a note */
      str newTi;
      str newDes;
      std::cout << "enter the index of the note: ";
      std::cin >> index;
      std::cin.ignore();
      std::cout
          << "enter the new title of the note (leave blank for skiping): ";
      std::getline(std::cin, newTi);
      std::cout << "enter the new description of the note (leave blank for "
                   "skiping): ";
      std::getline(std::cin, newDes);
      notes[index - 1].edit(newTi, newDes);
      break;
    }

    case 5: { /* switch position of notes */
      std::cout << "Which note to switch?: ";
      std::cin >> index;
      std::cout << "With which index?: ";
      std::cin >> target;
      switchPos(notes, index - 1, target - 1);
      break;
    }

    case 6: { /* move a note */
      std::cout << "Note index to move: ";
      std::cin >> index;
      std::cout << "New position index: ";
      std::cin >> target;
      changePos(notes, index - 1, target - 1);
      break;
    }

    case 7: /* exit */
      on = false;
      std::cout << "Closing the program...\n";
      break;

    default:
      std::cout << "Invalid option.\n";
    }

    std::cout << "Done!\n";
  } while (on);

  //saving to json
  nlohmann::json arr = nlohmann::json::array(); // 🔹 Step 1
  for (const Note& note : notes) {              // 🔹 Step 2
    arr.push_back({                             // 🔹 Step 3
      {"title", note.title},
      {"description", note.description}
    });
  }
  json::writeJson(data, arr);

  return 0;
} // main End

// Function defination

void displayNotes(std::vector<Note> &arr) {
  for (int i = 0; i < arr.size(); i++) {
    std::cout << "------------------------\n";
    std::cout << i + 1 << ". " << arr[i].title << '\n'
              << arr[i].description << '\n';
    std::cout << "------------------------\n";
  }
}

void removeNote(std::vector<Note> &vec, int index) {
  if (index >= 1 && index <= vec.size()) {
    vec.erase(vec.begin() + index - 1);
  } else {
    std::cout << "Invalid index!\n";
  }
}

void switchPos(std::vector<Note> &arr, int index, int targetIndex) {
  Note temp = arr[targetIndex];
  arr[targetIndex] = arr[index];
  arr[index] = temp;
}

void changePos(std::vector<Note> &arr, int index, int target) {
  if (index < 0 || index >= arr.size() || target < 0 || target > arr.size())
    return;

  Note temp = arr[index];
  arr.erase(arr.begin() + index);

  if (target > index)
    target -= 1;

  arr.insert(arr.begin() + target, temp);
}
