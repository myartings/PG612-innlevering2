I innleveringen har jeg implementert følgende slik oppgave teksten beskriver:

-Rendering av lyset sitt "point of view" til en FBO som senere kan brukes til å lage skygger med shadowmap teknikk og å rendre en depth-dump.

-Rendering av depth FBOet til skjermen for å vise dybdeverdiene til det som rendres. Gråfarge verdien blir modifisert basert på near og far clip plane 
 for å få mer definerte fargeverdier (mørkere nærme, lysere langt fra). Dette gjøres i fragment shaderen.

-Muligheten til å toggle rendering av FBO depth texturen til skjermen. Det rendres semi-transperant. Alpha kan endres med en GUI Slider.

-Skygge-casting med shadowmapping teknikk

-Egne shadere for å rendre wireframe og hidden-line av scenen. Wireframe renderingen bruker geometri shaderen til å outputte linjer, og
 hidden-line shaderen bruker de barycentrice koordinatene til hver trekant for å tegne wireframe over modellene i ett renderpass.

-Diffus lighting av objektene i scenen ved å sende inn den vedlagte cubemappen til fragment shaderen, og bruke normalen til fragmentene  til å slå opp i cubemappet og finne den diffuse fargen. 


For å gi muligheten til å tweake på linjetykkelsen på hidden-line renderingen har jeg laget et lite enkelt GUI system med slidere man kan modifisere for å endre tykkelse og anti-aliasing verdier på linjene. De GUI relaterte klassene er flyttet for seg i en egen mappe i VS prosjektet (Not-directly-relate-to-assignment classes) for å holde dem avskilt fra det som er direkte relatert til innleveringen.

Med GUI-slider kan man også velge å endre hvorvidt man kun vil bruke diffuse fargen fra diffuse-mapet, mixe den orginale diffuse fargen med fargen fra mappet, eller kun bruke den orginale diffuse fargen.

Jeg har også lagt til en litt mer avansert modell enn det simple cube-rommet som følger med for å bedre kunne demonstrere hvordan skyggene ser ut når de faller på mer ugjevne overlater. I den sammenheng har jeg også lagt til en skybox som ikke blir påvirket av skyggene, bare for å få alt til å se litt penere ut. Man kan bytte mellom det nye rommet og den orginale cuben ved å trykke på radiobutons jeg også har laget med det enkle GUI systemet.

Jeg har gjort en liten forbedring på skygge-shaderen. Ved å gjøre flere oppslag i shadowmapet med offset og dithering for å gjøre kantene på skyggene gjevnere. Dette fjerner både noe av staircasing effekten man får med lav oppløsning på shadow FBOet og gir en mer mooth overgang i kantene ("fake smooth shadows").

I koden blir enkelte matriser under renderingen laget likt opptil to ganger. Her kunne jeg optimalisert ved å lage den en gang også sende en referanse, men for å holde koden så oversiktelig som mulig velger jeg heller å offre minimalt med performance for bedre readability.

Referanser brukt:
Mark J. Kilgard (Ukjent år). "Shadow mapping with today's openGL Hardware". Kan sees på: https://developer.nvidia.com/sites/default/files/akamai/gamedev/docs/GDC01_Shadows.pdf

Nvidia White Paper (2007). "Solid Wireframe". Kan sees på: http://tommyhinks.files.wordpress.com/2012/02/nvidia_solid_wireframe.pdf