I innleveringen har jeg implementert f�lgende slik oppgave teksten beskriver:

-Rendering av lyset sitt "point of view" til en FBO som senere kan brukes til � lage skygger med shadowmap teknikk og � rendre en depth-dump.

-Rendering av depth FBOet til skjermen for � vise dybdeverdiene til det som rendres. Gr�farge verdien blir modifisert basert p� near og far clip plane 
 for � f� mer definerte fargeverdier (m�rkere n�rme, lysere langt fra). Dette gj�res i fragment shaderen.

-Muligheten til � toggle rendering av FBO depth texturen til skjermen. Det rendres semi-transperant. Alpha kan endres med en GUI Slider.

-Skygge-casting med shadowmapping teknikk

-Egne shadere for � rendre wireframe og hidden-line av scenen. Wireframe renderingen bruker geometri shaderen til � outputte linjer, og
 hidden-line shaderen bruker de barycentrice koordinatene til hver trekant for � tegne wireframe over modellene i ett renderpass.

-Diffus lighting av objektene i scenen ved � sende inn den vedlagte cubemappen til fragment shaderen, og bruke normalen til fragmentene  til � sl� opp i cubemappet og finne den diffuse fargen. 


For � gi muligheten til � tweake p� linjetykkelsen p� hidden-line renderingen har jeg laget et lite enkelt GUI system med slidere man kan modifisere for � endre tykkelse og anti-aliasing verdier p� linjene. De GUI relaterte klassene er flyttet for seg i en egen mappe i VS prosjektet (Not-directly-relate-to-assignment classes) for � holde dem avskilt fra det som er direkte relatert til innleveringen.

Med GUI-slider kan man ogs� velge � endre hvorvidt man kun vil bruke diffuse fargen fra diffuse-mapet, mixe den orginale diffuse fargen med fargen fra mappet, eller kun bruke den orginale diffuse fargen.

Jeg har ogs� lagt til en litt mer avansert modell enn det simple cube-rommet som f�lger med for � bedre kunne demonstrere hvordan skyggene ser ut n�r de faller p� mer ugjevne overlater. I den sammenheng har jeg ogs� lagt til en skybox som ikke blir p�virket av skyggene, bare for � f� alt til � se litt penere ut. Man kan bytte mellom det nye rommet og den orginale cuben ved � trykke p� radiobutons jeg ogs� har laget med det enkle GUI systemet.

Jeg har gjort en liten forbedring p� skygge-shaderen. Ved � gj�re flere oppslag i shadowmapet med offset og dithering for � gj�re kantene p� skyggene gjevnere. Dette fjerner b�de noe av staircasing effekten man f�r med lav oppl�sning p� shadow FBOet og gir en mer mooth overgang i kantene ("fake smooth shadows").

I koden blir enkelte matriser under renderingen laget likt opptil to ganger. Her kunne jeg optimalisert ved � lage den en gang ogs� sende en referanse, men for � holde koden s� oversiktelig som mulig velger jeg heller � offre minimalt med performance for bedre readability.

Referanser brukt:
Mark J. Kilgard (Ukjent �r). "Shadow mapping with today's openGL Hardware". Kan sees p�: https://developer.nvidia.com/sites/default/files/akamai/gamedev/docs/GDC01_Shadows.pdf

Nvidia White Paper (2007). "Solid Wireframe". Kan sees p�: http://tommyhinks.files.wordpress.com/2012/02/nvidia_solid_wireframe.pdf