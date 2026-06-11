# Textový procesor v C

Konzolový textový procesor v jazyku C, ktorý načítava riadky textu a vykonáva operácie s reťazcami pomocou príkazov zadávaných zo štandardného vstupu.

## Čo projekt robí

Program pracuje s dvoma ukazovateľmi (`sp` – start pointer, `ep` – end pointer) v rámci jedného riadku textu a umožňuje:

**I/O operácie**
- `in <text>` – načítanie textu do pamäte
- `out op/mem/range` – výpis textu, pamäte alebo vybraného rozsahu

**Pohyb v texte**
- `move sp/ep <n>` – posun ukazovateľa o n pozícií
- `start/end sp/ep` – presun ukazovateľa na začiatok/koniec

**Operácie so slovami**
- `first`, `last` – výber prvého/posledného slova
- `next`, `prev` – presun na ďalšie/predošlé slovo

**Operácie s reťazcami**
- `del` – vymazanie vybraného rozsahu
- `crop` – orezanie textu na vybraný rozsah
- `copy` – skopírovanie rozsahu do pamäte
- `insert mem/<n>` – vloženie obsahu pamäte alebo n medzier
- `replace` – nahradenie rozsahu obsahom pamäte

**Ošetrenie chýb**
- `ERR_OVERFLOW` – prekročenie maximálnej dĺžky reťazca
- `ERR_POSITION` – neplatná pozícia ukazovateľov
- `ERR_OUT_OF_RANGE` – ukazovateľ mimo rozsahu

## Použité technológie
- Jazyk C (štandardná knižnica) – `stdio.h`, `string.h`, `ctype.h`, `stdlib.h`
- Práca s ukazovateľmi (pointrami) na znaky
- Kompilátor GCC
