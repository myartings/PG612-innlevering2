I innleveringen har jeg implementert f�lgende slik oppgave teksten beskriver:

-Rendering av lyset sitt "point of view" til en FBO, en version for � rendre til skjermen og en annen version til � bruke til  shadowmapping
-Rendering av depth FBOet til skjermen for � vise dybdeverdiene til det som rendres. Gr�fargen blir normalisert basert p� near og far clip plane.
-Muligheten til � toggle rendering av FBO depth texturen til skjermen. Det rendres semi-transperant.
-Skygge-casting med shadowmapping teknikk
-Egen shader for � rendre wireframe og hidden-line av scenen wireframe renderingen bruker geometri shaderen til � outputte linjer, og
 hidden-line shaderen bruker de barycentrice koordinatene til hver trekant for � tegne wireframe opp� modellene.
-Diffus lighting av objektene i scenen ved � sende inn den vedlagte cubemappen til fragment shaderen, og bruke normalen til fragmentene  til � sl� opp i cubemappet og finne den diffuse fargen.


For � gi muligheten til � tweake p� linjetykkelsen p� hidden-line renderingen har jeg laget et lite enkelt GUI system med slidere man kan modifisere for � endre tykkelse og anti-aliasing verdier p� linjene. De GUI relaterte klassene er flyttet for seg i en egen mappe i VS prosjektet (Not-directly-relate-to-assignment classes) for � holde dem avskilt fra det som er direkte relatert til innleveringen.

Jeg har ogs� lagt til en litt mer avansert modell enn det simple cube-rommet som f�lger med for � bedre kunne demonstrere hvordan skyggene ser ut n�r de faller p� mer ugjevne overlater. I den sammenheng har jeg ogs� lagt til en skybox som ikke blir p�virket av skyggene, bare for � f� alt til � se litt penere ut. Man kan bytte mellom det nye rommet og den orginale cuben ved � trykke p� radiobutons jeg ogs� har laget med det enkle GUI systemet.

Jeg har gjort en liten forbedring p� skygge-shaderen fra det vi gjorde i �vningstimen, ved � gj�re flere oppslag i shadow texturen med offset og dithering for � gj�re kantene p� skyggene gjevnere. Dette fjerner b�de noe av staircasing effekten man f�r med lav oppl�sning p� shadow FBOet og gir en mer smooth overgang i kantene.


Referanser brukt:
Mark J. Kilgard (Ukjent �r). "Shadow mapping with today's openGL Hardware". Kan sees p�: https://developer.nvidia.com/sites/default/files/akamai/gamedev/docs/GDC01_Shadows.pdf

Nvidia White Paper (2007). "Solid Wireframe". Kan sees p�: http://tommyhinks.files.wordpress.com/2012/02/nvidia_solid_wireframe.pdf