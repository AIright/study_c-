//
// Created by alright on 24.12.17.
//
/* Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.
 * Считайте, что в каждый год может произойти не более одного изменения фамилии и не более одного изменения имени.
 * При этом с течением времени могут открываться всё новые факты из прошлого человека, поэтому года́
 * в последовательных вызовах методов ChangeLastName и ChangeFirstName не обязаны возрастать.
 * Гарантируется, что все имена и фамилии непусты.
 * Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом имя и
 * фамилию человека по состоянию на конец данного года.
 * Если к данному году не случилось ни одного изменения фамилии и имени, верните строку "Incognito".
 * Если к данному году случилось изменение фамилии, но не было ни одного изменения имени,
 * верните "last_name with unknown first name".
 * Если к данному году случилось изменение имени, но не было ни одного изменения фамилии,
 * верните "first_name with unknown last name".
 * Дополните класс из предыдущей задачи «Имена и фамилии — 1» методом GetFullNameWithHistory:
 * В отличие от метода GetFullName, метод GetFullNameWithHistory должен вернуть не только последние имя и фамилию
 * к концу данного года, но ещё и все предыдущие имена и фамилии в обратном хронологическом порядке.
 * Если текущие факты говорят о том, что человек два раза подряд изменил фамилию или имя на одно и то же,
 * второе изменение при формировании истории нужно игнорировать
 */

#ifndef STUDY_C_NAMESANDSURENAMES1_H
#define STUDY_C_NAMESANDSURENAMES1_H

#include <string>
#include <algorithm>
#include <iostream>
#include <locale>
#include <vector>
#include <map>
#include <iterator>
#include <sstream>

using namespace std;

struct person {
    // фиксируем изменение имени
    map<int, string> name;
    // список дат изменения имени для итерации
    vector<int> names_years;
    // фиксируем изменение фамилии
    map<int, string> surename;
    // список дат изменения фамилии для итерации
    vector<int> surenames_years;
};

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        // добавить факт изменения имени на first_name в год year
        person1.name[year] = first_name;
        person1.names_years.push_back(year);
        // сортируем вектор дат изменения имени
        sort(person1.names_years.begin(), person1.names_years.end());
    }

    void ChangeLastName(int year, const string& last_name) {
        // добавить факт изменения фамилии на last_name в год year
        person1.surename[year] = last_name;
        person1.surenames_years.push_back(year);
        // сортируем вектор дат изменения фамилии
        sort(person1.surenames_years.begin(), person1.surenames_years.end());
    }

    string GetFullName(int year) {
        // получить имя и фамилию по состоянию на конец года year
        // год меньше минимального или дат нет вовсе
        if ((person1.names_years.empty() || person1.names_years[0] > year)
            && (person1.surenames_years.empty() || person1.surenames_years[0] > year)) {
            return "Incognito";
        // год больше максимального и изменения происходили (вектор дат не пустой)
        } else if ((!person1.names_years.empty() && person1.names_years[person1.name.size() - 1] <= year)
                   && (!person1.surenames_years.empty() && person1.surenames_years[person1.surename.size() - 1] <= year)){
        // выводим изменения в последний год
            return person1.name[person1.names_years[person1.name.size() - 1]] + " "
                   + person1.surename[person1.surenames_years[person1.surename.size() - 1]];
        // если дата изменения имени меньше минимальной или дат нет
        } else if (person1.names_years.empty() || person1.names_years[0] > year) {
            // то итерируем по фамилиям и выводим последнее изменение к дате year
            int buf = Iterate(person1.surenames_years, year);
            return person1.surename[buf] + " with unknown first name";
        // если дата изменения фамилии меньше минимальной или дат нет
        } else if (person1.surenames_years.empty() || person1.surenames_years[0] > year) {
            // то итерируем по именам и выводим последнее изменение к дате year
            int buf = Iterate(person1.names_years, year);
            return person1.name[buf] + " with unknown last name";
        } else {
            // значит дата year внутри списков дат изменений имени и фамилии
            // итерируем по датам изменений, находим ближайшие, выводим
            int bufs = Iterate(person1.surenames_years, year);
            int bufn = Iterate(person1.names_years, year);
            return person1.name[bufn] + " " + person1.surename[bufs];
        }
    }

    string GetFullNameWithHistory(int year) {
        // получить все имена и фамилии по состоянию на конец года year
        // год меньше минимального или дат нет вовсе
        if ((person1.names_years.empty() || person1.names_years[0] > year)
            && (person1.surenames_years.empty() || person1.surenames_years[0] > year)) {
            return "Incognito";
        // год больше максимального и изменения происходили (вектор дат не пустой)
        } else if ((!person1.names_years.empty() && person1.names_years[person1.name.size() - 1] <= year) &&
                (!person1.surenames_years.empty() && person1.surenames_years[person1.surename.size() - 1] <= year)){
            // выводим изменения в последний год
            return person1.name[person1.names_years[person1.name.size() - 1]] +
                    IteateHistory(person1.names_years, person1.names_years[person1.names_years.size() - 1], person1.name, 0) +
                    person1.surename[person1.surenames_years[person1.surename.size() - 1]] +
                    IteateHistory(person1.surenames_years, person1.surenames_years[person1.surenames_years.size() - 1], person1.surename, 1);
            // если дата изменения имени меньше минимальной или дат нет
        } else if (person1.names_years.empty() || person1.names_years[0] > year) {
            // то итерируем по фамилиям и выводим последнее изменение к дате year
            int buf = Iterate(person1.surenames_years, year);
            return person1.surename[buf] +
                    IteateHistory(person1.surenames_years, buf, person1.surename, 0) +
                    "with unknown first name";
            // если дата изменения фамилии меньше минимальной или дат нет
        } else if (person1.surenames_years.empty() || person1.surenames_years[0] > year) {
            // то итерируем по именам и выводим последнее изменение к дате year
            int buf = Iterate(person1.names_years, year);
            return person1.name[buf] +
                    IteateHistory(person1.names_years, buf, person1.name, 0) +
                    "with unknown last name";
        } else {
            // значит дата year внутри списков дат изменений имени и фамилии
            // итерируем по датам изменений, находим ближайшие, выводим
            int bufs = Iterate(person1.surenames_years, year);
            int bufn = Iterate(person1.names_years, year);
            return person1.name[bufn] +
                    IteateHistory(person1.names_years, bufn, person1.name, 0) +
                    person1.surename[bufs] +
                    IteateHistory(person1.surenames_years, bufs, person1.surename, 1);
        }
    }

private:
    // приватные поля
    person person1;
    // функция итерации по векторам дат и вывода ближайшей к year даты
    int Iterate(const vector<int>& years, const int& year) {
        int buf = 0;
        for (const auto& i : years) {
            if (i > year) {
                break;
            }
            buf = i;
        }
        return buf;
    }

    // функция итерации с историей
    string IteateHistory(const vector<int>& years, const int& year,
            map<int, string>& names, const bool& last) {
        string result = " ";
        vector<string> buf;
        // собираем в порядке изменения все уникальные фамилии
        for (auto& i : names) {
            if (i.first < year) {
                if (buf.empty() || (i.second != buf[buf.size() - 1])) {
                    buf.push_back(i.second);
                }
            } else {
                break;
            }
        }
        // если последнее изменение фамилии равно текущей, то удаляем
        if (!buf.empty() && buf[buf.size() - 1] == names[year]) {
            buf.resize(buf.size() - 1);
        }
        // если фамилия менялась, то формируем строку с историей
        if (!buf.empty()) {
            result += "(";
            reverse(buf.begin(), buf.end());
            for (auto& i : buf) {
                if (i == buf[buf.size() - 1]) {
                    result += (i + ") ");
                } else {
                    result += (i + ", ");
                }
            }
        }
        // придется удалять пробел в конце, если функция формирует окончание строки
        if (last) {
            result.resize(result.size() - 1);
            return result;
        }
        return result;
    }

};

/* REAL SOLUTION
 * #include <map>
#include <string>

// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string>& names, int year) {
  string name;  // изначально имя неизвестно

  // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
  for (const auto& item : names) {
    // если очередной год не больше данного, обновляем имя
    if (item.first <= year) {
      name = item.second;
    } else {
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      break;
    }
  }

  return name;
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }
  string GetFullName(int year) {
    // получаем имя и фамилию по состоянию на год year
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);

    // если и имя, и фамилия неизвестны
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";

    // если неизвестно только имя
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";

    // если неизвестна только фамилия
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";

    // если известны и имя, и фамилия
    } else {
      return first_name + " " + last_name;
    }
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
};

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

vector<string> FindNamesHistory(const map<int, string>& names_by_year,
                                int year) {
  vector<string> names;
  // перебираем всю историю в хронологическом порядке
  for (const auto& item : names_by_year) {
    // если очередное имя не относится к будущему и отличается от предыдущего,
    if (item.first <= year && (names.empty() || names.back() != item.second)) {
      // добавляем его в историю
      names.push_back(item.second);
    }
  }
  return names;
}

string BuildJoinedName(vector<string> names) {
  // нет истории — имя неизвестно
  if (names.empty()) {
    return "";
  }
  // меняем прямой хронологический порядок на обратный
  reverse(begin(names), end(names));

  // начинаем строить полное имя с самого последнего
  string joined_name = names[0];

  // перебираем все последующие имена
  for (int i = 1; i < names.size(); ++i) {
    if (i == 1) {
      // если это первое «историческое» имя, отделяем его от последнего скобкой
      joined_name += " (";
    } else {
      // если это не первое имя, отделяем от предыдущего запятой
      joined_name += ", ";
    }
    // и добавляем очередное имя
    joined_name += names[i];
  }

  // если в истории было больше одного имени, мы открывали скобку — закроем её
  if (names.size() > 1) {
    joined_name += ")";
  }
  // имя со всей историей готово
  return joined_name;
}

// см. решение предыдущей задачи
string BuildFullName(const string& first_name, const string& last_name) {
  if (first_name.empty() && last_name.empty()) {
    return "Incognito";
  } else if (first_name.empty()) {
    return last_name + " with unknown first name";
  } else if (last_name.empty()) {
    return first_name + " with unknown last name";
  } else {
    return first_name + " " + last_name;
  }
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }

  string GetFullName(int year) {
    // найдём историю изменений имени и фамилии
    // в данном случае это излишне, так как нам достаточно узнать последние имя и фамилию, но почему бы не использовать готовые функции?
    const vector<string> first_names_history = FindFirstNamesHistory(year);
    const vector<string> last_names_history = FindLastNamesHistory(year);

    // подготовим данные для функции BuildFullName: возьмём последние имя и фамилию или оставим их пустыми, если они неизвестны
    string first_name;
    string last_name;
    if (!first_names_history.empty()) {
      first_name = first_names_history.back();
    }
    if (!last_names_history.empty()) {
      last_name = last_names_history.back();
    }
    return BuildFullName(first_name, last_name);
  }

  string GetFullNameWithHistory(int year) {
    // получим полное имя со всей историей
    const string first_name = BuildJoinedName(FindFirstNamesHistory(year));
    // получим полную фамилию со всей историей
    const string last_name = BuildJoinedName(FindLastNamesHistory(year));
    // объединим их с помощью готовой функции
    return BuildFullName(first_name, last_name);
  }

private:
  vector<string> FindFirstNamesHistory(int year) {
    return FindNamesHistory(first_names, year);
  }
  vector<string> FindLastNamesHistory(int year) {
    return FindNamesHistory(last_names, year);
  }

  map<int, string> first_names;
  map<int, string> last_names;
};*/


#endif //STUDY_C_NAMESANDSURENAMES1_H
