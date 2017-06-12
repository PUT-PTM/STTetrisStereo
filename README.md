# STTetrisStereo

<b><i>Overview:</i></b> Projekt zakłada stworzenie gry bazującej na kultowej grze Tetris.
Sterowanie będzie zrealizowane za pomocą 8 przyciskowego panelu, a efekty wyświetlane na wyświetlaczu od starego
telefonu komórkowego. W założeniach projektu występuje też odtwarzanie dźwięków oraz melodii.

<b><i>Descriptions:</i></b> Projekt przedstawia kultową gre Tetris wykonaną na mikroprocesorze STM32F407VGT6. Sterowanie zrealizowane jest za pomocą 8 przyciskowego panelu. Efekty ukazywane są na wyświetlaczu od noki 5110. Dodatkowo podczas gry usłyszeć można kultową muzykę z Tetrisa oraz przyjemny dźwięk zdobywania punktów po przez zapełnienia całego wiersza blokami.
Wyświetlanie oparte jest na podzieleniu ekranu na chunki, stworzeniu tabeli i na jej podstawie dochadzi do sprawdzania czy w danym miejscu znajduje się już blok. Figury generowane są pseudolosowo. Obrót figur zaczyna się od sprawdzenia czy w pozycji wynikowej nie istnieje kolizja z istniejącym już blokiem. Gra posiada system rankingowy.

<b><i>Tools:</i></b> CooCox IDE 1.7.6
      Język programowania C
      STM32F407VGT6
      
<b><i>How to run:</i></b> Program obsługiwany jest za pomocą przycisków, ekran należy ustawić pionowo (krótsze boki są górna i dolną częsćią), następnie postępować wg informacji wyświetlanych na ekranie.

<b><i>How to compile:</i></b> Nie wymaga podejmowania żadnych dodatkowych kroków

<b><i>Atributions:</i></b> Biblioteka do obsługi wyświetlacza https://stm32f4-discovery.net/pcd8544-nokia-33105110-lcd-stm32f429-discovery-library/ by Tilen Majerle


<b><i>Future improvements:</i></b> <br>
-Dadanie innych trybów gry <br>
-Ulepszenie modelu obrotu figur<br>
-Stworzenie obudowy urządzenia<br>
-Stworzeni róznych poziomów trudności po przez manipulowanie szybkoscią opadania bloków <br>
-Dodanie funkcji opierających się o używanie niewykorzystanych przycisków<br>

<b><i>License:</i></b> MIT(X11)

<b><i>Credits:</i></b> Piotr Pawłowski and Łukasz  Kowalewski
<p style='color:red'>
The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.<br>
Supervisor: Marek Kraft/Michał Fularz/Tomasz Mańkowski/Adam Bondyra
</p>

