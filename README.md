# parametri sustava
- najbolji parametri sustava se nalaze u media/ok.yml

# note
- build bi trebao raditi dobro ako je na sustavu installiran Eigen c++ library, Cmake bi trebao s interneta pullati nanospline header i dodati ga u build, tako da je za build potreban internet

- skripte za vizualizaciju brzine i kurvature tokom jedne voznje se nazale u scripts/custom_scripts
- dio koda koji logga brzinu i kurvaturu je komentiran tako da se novi runnovi nece loggati u file, ali u projektu se nalaze prethodno snimljene brzine i kurvature u cvs fileovima koji se mogu koristiti za vizualizaciju tih podataka