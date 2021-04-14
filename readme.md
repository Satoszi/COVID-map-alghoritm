# Algorytm genetyczny rozwiązujący problem izolacji. 

Problem polega na tym, żę mamy pewną mapę, na której należy rozstawić jak najwięcej osób, tak aby nie zarażały się wzajemnie. 

Algorytm: Wybieramy pewną liczbę N losowych ustawień osób na mapie, a następnie łączy je ze sobą w różne sposoby (genetycznie krzyżuje), jednocześnie usuwając najgorsze rezultaty. W ten sposób krzyżujemy ze sobą coraz lepsze rozstawienia osób.