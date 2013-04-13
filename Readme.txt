I innleveringen har jeg implementert følgende slik oppgave teksten beskriver:

-Rendering av lyset sitt "point of view" til en FBO, en version for å rendre til skjermen og en annen version til å bruke til  shadowmapping
-Rendering av depth FBOet til skjermen for å vise dybdeverdiene til det som rendres. Gråfargen blir normalisert basert på near og far clip plane.
-Muligheten til å toggle rendering av FBO depth texturen til skjermen. Det rendres semi-transperant.
-Skygge-casting med shadowmapping teknikk
-Egen shader for å rendre wireframe og hidden-line av scenen wireframe renderingen bruker geometri shaderen til å outputte linjer, og
 hidden-line shaderen bruker de barycentrice koordinatene til hver trekant for å tegne wireframe oppå modellene.
-Diffus lighting av objektene i scenen ved å sende inn den vedlagte cubemappen til fragment shaderen, og bruke normalen til fragmentene  til å slå opp i cubemappet og finne den diffuse fargen.


For å gi muligheten til å tweake på linjetykkelsen på hidden-line renderingen har jeg laget et lite enkelt GUI system med slidere man kan modifisere for å endre tykkelse og anti-aliasing verdier på linjene. De GUI relaterte klassene er flyttet for seg i en egen mappe i VS prosjektet (Not-directly-relate-to-assignment classes) for å holde dem avskilt fra det som er direkte relatert til innleveringen.

Jeg har også lagt til en litt mer avansert modell enn det simple cube-rommet som følger med for å bedre kunne demonstrere hvordan skyggene ser ut når de faller på mer ugjevne overlater. I den sammenheng har jeg også lagt til en skybox som ikke blir påvirket av skyggene, bare for å få alt til å se litt penere ut. Man kan bytte mellom det nye rommet og den orginale cuben ved å trykke på radiobutons jeg også har laget med det enkle GUI systemet.

Jeg har gjort en liten forbedring på skygge-shaderen fra det vi gjorde i øvningstimen, ved å gjøre flere oppslag i shadow texturen med offset og dithering for å gjøre kantene på skyggene gjevnere. Dette fjerner både noe av staircasing effekten man får med lav oppløsning på shadow FBOet og gir en mer smooth overgang i kantene.


Referanser brukt:
Mark J. Kilgard (Ukjent år). "Shadow mapping with today's openGL Hardware". Kan sees på: https://developer.nvidia.com/sites/default/files/akamai/gamedev/docs/GDC01_Shadows.pdf

Nvidia White Paper (2007). "Solid Wireframe". Kan sees på: http://tommyhinks.files.wordpress.com/2012/02/nvidia_solid_wireframe.pdf