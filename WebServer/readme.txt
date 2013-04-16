Tout d'abord, veillez à bien ouvrir le projet en UTF-8.

Ensuite, nous avons une class abstraite Task utilisée pour bien marquer le fait que les différentes tâches ConnectionTask, ProcessTask et ReadTask ont des propriétés similaires.
Il ne s'agit pas de classes quelconques mais des objets qui s'occupent de gérer d'une façon ou d'une autre une connection et ses demandes.
C'est aussi bien plus joli que d'implémenter Runnable dans chacune de ces classes séparément.

Dans le TaskBuffer:
Nous avons choisi d'enlever toutes les permissions de la Sémaphore emptyBuffer car c'est il est beaucoup plus intuitif d'ajouter une permission quand on ajoute des Tasks dans le buffer.
Nous avons de plus une Sémaphore nbUsers qui nous permet de nous assurer qu'un seul Worker ne puisse accéder en même temps à buffer.
Nous avons fait attention au fait que l'on vérifie en premier que le nombre de messages dans buffer est satisfaisant avant de demander la permission pour modifier le buffer.

Nous avons utilisé les moniteurs Java plutôt que les conditions dans BlockingCounter tout simplement car nous les avons vus en cours et que nous sommes plus familiers avec.

Question: Is it necessary to have two buﬀers (and two sets of threads) or is it possible to schedule all tasks using just one buﬀer?

Yes, it is necessary to have different buffers for the different tasks.
Two cases occurs:
	- if we have too much request from a single client, other users will have to wait for a connection until at least one worker is free.
	It can be worse if the client asks big data because it would a while to process.
	This is not a worst case scenario because eventually a worker wil be free.
	
	- if we have as many connections as the number of workers, we have a REALLY big problem here.
	Each worker will be busy managing a connection (read,...) so there will be no one to process the request.
	That implies that no client will get the response to its request.
	This is a very bad scenario because there no way to fix it.
	
In conclusion it is pretty important to have these two buffers.