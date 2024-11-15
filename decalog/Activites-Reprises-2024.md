
# Gilles et Damien :

Pour la revue du projet Reprises, nous n'avons pas de publications cette année. Mais nous avons quelques "points/delivrables" qui peuvent être, il me semble, valorisés auprès de l'Institut.
- Depuis aout-septembre nous travaillons sur le Real Time Analysis (RTA) de LHCb : Allen. Allen est un HLT software qui reconstruit partiellement les évènements et qui exploite la puissance des GPU.
- Concernant le master project EPOS-HardProbe. Damien a travaillé sur l'architecture du code EPOS. A partir d'un code monolitique et patrimoine (du laboratoire et de l'Institut) écrit en Fortran, il a mis en place une architecture extensible et modulaire qui permet de l'interfacer avec de nouveaux modules. Cette année le module Jets à été ajouté à EPOS. La difficulté principale a été de faire passer les nombreuses variables globales (COMMON) en variables encapsulées et dynamiques.
- Elaboration d'un cours d'introduction à l'IA pour les masters de Physique Fondamentale et Applications 1er année. Attention ce cours n'est pas que sur le Deep Learning. Il introduit
les méthodes/algorithmes "Classiques" largement utilisées en physique depuis des dizaines d'années (Decision Tree, Machine à vecteur de Support, Réduction de la dimensionnalité, Clustering, méthodes ensemblistes). Donc plus largement sur les méthodes et algorithmes ... en lien avec Reprises
- Divers formations git/python (Damien)


# École Gray Scott Reloaded
Alice, David, Hadrien, Vincent, Jean-Marc, Pierre, Joël, Sébastien, Nabil + Catherine Biscarat qui a gérer le pôle de l'école à Toulouse.

L'école traite de l’optimisation des calculs sur différents types de matériels (CPU, GPU), en présentant leurs caractéristiques respectives, architectures et goulots d’étranglements. Elle porte d’une part sur les méthodes d’optimisation génériques applicables à tout type de matériel, et d’autre part sur les différentes bibliothèques, technologies et langages dont on dispose pour atteindre la meilleure performance possible. Idéalement, la performance crête de la machine.

- Matériels: CPU, GPU.
- Langages : C++17, C++20, CUDA, Fortran, Rust, Python
- Bibliothèques : SYCL, Eve, Numpy, cunumerics, legate, Jax, Thrust.
- Compilateurs : G++, Clang++, nvc++, gfortran, nvfortran, dpc++.
- Outils de Profilage : Valgrind, Maqao, Perf, NSight, Malt et NumaProf

Toutes les méthodes sont illustrées sur des exemples simples, comme des produits de Hadamard, des réductions, des calculs de barycentres et des produits de matrice afin d'être appliquées à un problème unique : la simulation d'une réaction de Gray Scott. Ce problème est suffisamment simple pour être compris rapidement et suffisamment complexe pour que les compilateurs aient des difficultés à l’optimiser sans aide. Chaque méthode est déclinée en version simple, utilisant des options par défaut, et une ou plusieurs versions avancées, qui permettent de discuter et quantifier leurs avantages et inconvénients.

Cette école de calcul haute performance entièrement gratuite a eu lieu du 1er au 12 juillet 2024.
Le programme a été mis en place par Pierre en concertation avec les professeurs de l'école.
La communication et les 12 sites satellites ont été coordonnés par Maud Coppel du LAPP et Marie Lhande-pincemin et Karim Azoum de l'association TERATEC.
Une bande annonce de l'école est disponible [ici](https://www.youtube.com/watch?v=AbCfvTCvFFI&list=PLj_PwIXO9FR1rBjCj5fJWMP74Jof8UoRc&index=2).

## Les jeudis Gray Scott

Les [jeudis Gray Scott](https://indico.in2p3.fr/event/30939/page/3642-les-jeudis-gray-scott) sont un ensemble de 18 webinaires entre janvier et juin 2024 où ont été présenté un aspect, une technologie, une méthodologie ou un langage abordé pendant l'école de juillet.
Chaque professeur a préparé au moins deux webinaires pour présenter leur cours (partie CPU + partie GPU).

Ces webinaires ont été suivis en direct par plus de 900 personnes sur Zoom et totalisent à ce jour 3989 vues sur YouTube.

- 25/01/2024 -10h : Présentation de la Gray Scott School : Pierre Aubert [pdf](https://indico.in2p3.fr/event/31996/attachments/82448/122031/presentation_gray_scott_reloaded_2024.pdf) [YouTube](https://www.youtube.com/watch?v=r9iuEIXMLkA)
- 19/01/24 - 14h : Tests unitaires, une philosophie et une aide face à son logiciel : Sébastien Valat [pdf](https://lapp-owncloud.in2p3.fr/s/Bn3peD8f9i2o76G) [YouTube](https://www.youtube.com/watch?v=ey2h3H3jH8Q)
- 01/02/2024 -10h : Architecture CPU : Hadrien Grasland [pdf](https://indico.in2p3.fr/event/32095/attachments/82635/122376/ArchiCPU.pdf) [YouTube](https://www.youtube.com/watch?v=AZKMjf2jBXA)
- 08/02/2024 -10h : Précision des calculs : Vincent Lafage [pdf](https://indico.in2p3.fr/event/32201/attachments/82777/122786/Reprises_IJC_Precision_fra_web.pdf) [YouTube](https://www.youtube.com/watch?v=3wfCtziU4dQ)
- 15/02/2024 -10h : Allocations mémoires, pourquoi et comment profiler (MALT, NUMAPROF) : Sébastien Valat [pdf](https://indico.in2p3.fr/event/32202/attachments/82874/123141/2024-02-webniaire-jeudi-gray-scott-malt-numaprof-teasing.pdf) [YouTube](https://www.youtube.com/watch?v=zBmiVSCd1t4)
- 22/02/2024 -10h : Calcul en C++ 17/20/23 avec les `std::algorithm` : Pierre Aubert [pdf](https://indico.in2p3.fr/event/32334/attachments/82947/123219/presentation_webinaire_introdution_cpp_algorithms.pdf) [YouTube](https://www.youtube.com/watch?v=lb5MyO9bqdk)
- 29/02/2024 -10h : Le langage Rust : Hadrien Grasland [pdf](https://indico.in2p3.fr/event/32335/attachments/82899/123109/WhyRust_sans_animations.pdf) [YouTube](https://youtu.be/u_-PL_Rcn8A)
- 07/03/2024 -10h : Architecture GPU : Pierre Aubert [pdf](https://indico.in2p3.fr/event/32336/attachments/83170/123684/presentation_architecture_gpu.pdf) [YouTube](https://youtu.be/TBc-FRG9ER4)
- 08/03/2024 - 9h30 : Profilage de compilation C++ avec crofiler : Hadrien Grasland [pdf](https://indico.in2p3.fr/event/32002/attachments/82961/123246/crofiler.pdf) [YouTube](https://youtu.be/XhItkmkcW34)
- 14/03/2024 -10h : Calculer avec Sycl en C++ 20 sur CPU et GPU : David Chamont [pdf](https://indico.in2p3.fr/event/32337/attachments/83309/123982/sycl-landscape.pdf) [YouTube](https://youtu.be/4ir48WLvNzw)
- 21/03/2024 -10h : Fortran (langage, OpenACC) : Vincent Lafage [pdf](https://indico.in2p3.fr/event/32338/attachments/83434/124228/FortranFurious_IJC_web.pdf) [YouTube](https://youtu.be/xE3gPO9pon8)
- 28/03/2024 -10h : Calculer sur GPU en C++ 20 avec NVC++ et CUDA : Pierre Aubert [pdf](https://indico.in2p3.fr/event/32339/attachments/83697/124657/presentation_gpu_computing_with_cpp20_nvcpp_and_cuda.pdf) [YouTube](https://youtu.be/k1-3Bz87GKQ)
- 04/04/2024 -10h : Bibliothèque de calcul Eve en C++ 20 : Joël Falcou [YouTube](https://youtu.be/exsg50YkxJY)
- 11/04/2024 -10h : Calculer avec Numpy en Python : Alice Faure et Jean-Marc Colley [pdf](https://indico.in2p3.fr/event/32717/attachments/84014/125233/Python_CPU.pdf) [YouTube](https://youtu.be/TSShhpaxejw)
- 18/04/2024 -10h : Calculer avec Rust sur CPU et GPU : Hadrien Grasland [pdf](https://grasland.pages.in2p3.fr/how-to-compute-using-rust/) [YouTube](https://youtu.be/s_z7OgA8g_o)
- 02/05/2024 -10h : Calculer sur CPU et GPU en Fortran avec NVfortran et OpenACC : Vincent Lafage [pdf](https://indico.in2p3.fr/event/32719/attachments/84305/125774/FortranFuriousGPU_IJC_web.pdf) [YouTube](https://www.youtube.com/watch?v=xE3gPO9pon8&list=PLj_PwIXO9FR1rBjCj5fJWMP74Jof8UoRc&index=12&pp=iAQB)
- 16/05/2024 -10h : Python sur GPU : cunumerics / Legate / Tensorflow : Alice Faure, Jean-Marc Collet et Nabil Garroum [pdf](https://indico.in2p3.fr/event/32722/attachments/84528/126273/Python_GPU_JMC_AF_NG.pdf) [YouTube](https://youtu.be/cqx4JuMHcYI)
- 23/05/2024 - 10h : De CUDA à SYCL- Stratégies et Outils de Migration : Joël Falcou [Replay](https://indico.in2p3.fr/event/33160/attachments/84732/126667/Webinaire-Convertir-du-CUDA-en-Sycl-v1.mp4) [YouTube](https://youtu.be/TrViaSoEDcU)
-  06/06/2024 - 10h : Retour sur la conférence de Nvidia GTC 2024 - Rappel des événements précédents : Pierre Aubert [pdf](https://indico.in2p3.fr/event/32869/attachments/85386/128267/presentation_webinaire_retour_gtc_2024.pdf) [YouTube](https://www.youtube.com/watch?v=ewq-3AVTuBI&list=PLj_PwIXO9FR1rBjCj5fJWMP74Jof8UoRc&index=19&pp=iAQB)
- 13/06/2024 - 10h : Retour sur la conférence de Nvidia GTC 2024 : Pierre Aubert [pdf](https://indico.in2p3.fr/event/32724/attachments/85645/128266/presentation_webinaire_retour_gtc_2024.pdf) [YouTube](https://www.youtube.com/watch?v=2yTRnFMEQbA&list=PLj_PwIXO9FR1rBjCj5fJWMP74Jof8UoRc&index=20&pp=iAQB)


## Les cours

Le [programme de l'école](https://indico.in2p3.fr/event/30939/timetable/?view=standard_inline_minutes) est composé d'une semaine sur le calcul CPU et d'une semaine sur le calcul GPU.
La fin de la deuxième semaine a consisté en des retours d'expériences de personnes ayant profité de l'aide des professeurs de l'école et le dernier jour était une partie dite "bootstrap" ou les professeurs aidaient les participants résoudre leurs problèmes de calcul et d'optimisation.

- Introduction : Pierre Aubert [pdf](https://indico.in2p3.fr/event/30939/contributions/129743/attachments/82729/129210/2-lecture_plantage_du_decor.pdf)
- Architecture Matériel CPU : Hadrien Grasland [pdf](https://indico.in2p3.fr/event/30939/contributions/129747/attachments/82728/129054/ArchiCPU.pdf)
- Vectorisation VS Parallélisation ? : Vincent Lafage [ParallelComputing_IJC_eng_2024.pdf](https://indico.in2p3.fr/event/30939/contributions/129749/attachments/86045/129254/ParallelComputing_IJC_eng_2024.pdf) [Vectorization_IJC_eng_2024.pdf](https://indico.in2p3.fr/event/30939/contributions/129749/attachments/86045/129253/Vectorization_IJC_eng_2024.pdf)
- Qu'est ce que la compilation ? : Pierre Aubert [pdf](https://indico.in2p3.fr/event/30939/contributions/129744/attachments/86055/129224/5-lecture_introdution_compilation.pdf)
- Théorie et outils de Profilage : Hadrien Grasland [pdf](https://indico.in2p3.fr/event/30939/contributions/129755/attachments/85976/129055/Profilages.pdf)
- Précision numérique : Vincent Lafage [pdf](https://indico.in2p3.fr/event/30939/contributions/129770/attachments/82824/129255/Reprises_IJC_Precision_dual_2024.pdf)
- Vous avez dit tests unitaires ? : Sebastien VALAT [pdf](https://indico.in2p3.fr/event/30939/contributions/131506/attachments/82730/129596/2024-06-gray-scott-unit-tests.pdf)
- C++ 17/20/23 sur CPU : Pierre Aubert [pdf](https://indico.in2p3.fr/event/30939/contributions/129765/attachments/86223/129579/6-lecture_introdution_cpp_algorithms.pdf) [html](https://cta-lapp.pages.in2p3.fr/COURS/PERFORMANCE_WITH_STENCIL/)
- Fortran 2018 sur CPU : Vincent Lafage [pdf](https://indico.in2p3.fr/event/30939/contributions/129760/attachments/86108/129311/FortranFurious_IJC_web_2024.pdf)
- Une histoire de racine cubique : Vincent Lafage [pdf](https://indico.in2p3.fr/event/30939/contributions/129772/attachments/86129/129348/Reprises_IJC_PSA_vectorisation_2024.pdf)
- Évaluation de la précision numérique avec CADNA : David CHAMONT [pdf](https://indico.in2p3.fr/event/30939/contributions/131515/attachments/82872/129597/2024-07-gray-scott-malt.pdf)
- Rust sur CPU : Hadrien Grasland [html](https://grasland.pages.in2p3.fr/grayscott-with-rust)
- Calculer avec Python sur CPU : Numpy Scipy : Alice Faure et Jean-Marc Colley [html](https://gitlab.in2p3.fr/alice.faure/gray-scott-python/-/blob/main/tutorial/1_Python_CPU_Numpy.ipynb?ref_type=heads)
- Calculer avec Python sur CPU : Numba, SVML, multi-threading : Alice Faure et Jean-Marc Colley [html](https://gitlab.in2p3.fr/alice.faure/gray-scott-python/-/blob/main/tutorial/2_Python_CPU_Numba.ipynb?ref_type=heads)
- Calculer avec Python sur CPU : JAX : Alice Faure et Jean-Marc Colley [pdf](https://gitlab.in2p3.fr/alice.faure/gray-scott-python/-/blob/main/tutorial/3_Python_CPU_JAX_Part1.ipynb?ref_type=heads)
- Calculer avec Python sur CPU : JAX, Porting the Gray-Scott code : Alice Faure et Jean-Marc Colley [pdf](https://gitlab.in2p3.fr/alice.faure/gray-scott-python/-/blob/main/tutorial/4_Python_CPU_JAX_Part2.ipynb?ref_type=heads)
- Architecture GPU et calcul massivement parallèle : Pierre Aubert [pdf](https://indico.in2p3.fr/event/30939/contributions/131504/attachments/86224/129580/lecture_architecture_gpu.pdf)
- C++17/20:23 sur GPU avec NVC++ : Pierre Aubert [html](https://cta-lapp.pages.in2p3.fr/COURS/PERFORMANCE_WITH_STENCIL_GPU/index.html)
- Calcul en C++ 20 avec Eve : Joël Falcou
- Calculer avec Python sur GPU: CuPy : Alice Faure, Jean-Marc Colley, Nabil Garroum [html](https://gitlab.in2p3.fr/alice.faure/gray-scott-python/-/blob/main/tutorial/6_Python_GPU_Cupy.md?ref_type=heads)
- Calculer avec Python sur GPU: CuNumeric : Alice Faure, Jean-Marc Colley, Nabil Garroum [html](https://gitlab.in2p3.fr/alice.faure/gray-scott-python/-/blob/main/tutorial/5_Python_GPU_cuNumeric.md?ref_type=heads)
- Calculer avec Python sur GPU: JAX et TP : Alice Faure, Jean-Marc Colley, Nabil Garroum [html 1](https://gitlab.in2p3.fr/alice.faure/gray-scott-python/-/blob/main/tutorial/4_Python_GPU_JAX.md?ref_type=heads) [html 2](https://gitlab.in2p3.fr/alice.faure/gray-scott-python/-/blob/main/tutorial/4_Python_GPU_JAX_exo.md?ref_type=heads)
- Calculer avec Python sur GPU: Pytorch : Alice Faure, Jean-Marc Colley, Nabil Garroum [html 1](https://gitlab.in2p3.fr/alice.faure/gray-scott-python/-/blob/main/tutorial/7_Python_PytorchConv2d_GrayScott.ipynb?ref_type=heads) [html 2](https://gitlab.in2p3.fr/alice.faure/gray-scott-python/-/blob/main/tutorial/7_Pytorch_Tensor_Operations.ipynb?ref_type=heads)
- Sycl C++17 sur GPU : David CHAMONT [html](https://gitlab.in2p3.fr/CodeursIntensifs/grayscott/GrayScottSyclGpu)
- Rust sur GPU avec Vulkan : Hadrien Grasland [pdf](https://indico.in2p3.fr/event/30939/contributions/131523/attachments/86034/129179/VulkanIntro.pdf)
- Vincent Lafage : Fortran 2018 sur GPU
- Diffusion de particules dans la galaxie avec nvc++ : Yoann Génolini [pdf](https://indico.in2p3.fr/event/30939/contributions/131539/attachments/86234/129598/Gray_Scott_reloaded_Yoann_G%C3%A9nolini.pdf)
- Optimisation de la reconstruction de trace dans Dune en Python : Laura Zambelli [pdf](https://indico.in2p3.fr/event/30939/contributions/131540/attachments/86235/129599/lardon_grayscott.pdf)
- Portage Python de l'analyse CTA sur CPU et GPU : Vincent Pollet [pdf](https://indico.in2p3.fr/event/30939/contributions/131541/attachments/86236/129601/Gray_Scott_Battle_cta_analysis_porting_to_python_and_gpu.pdf)
- Impact du système sur les performances des applications : Sebastien VALAT [pdf](https://indico.in2p3.fr/event/30939/contributions/131542/attachments/86269/129713/2024-07-gray-scott-memory-details-old-theme.pdf)

## Les conteneurs des cours

Tous les cours fournis à l'école ont chacun plusieurs conteneurs optimisé pour leur usage (laptop, server, scheduler) et sont tous compatibles avec Docker, Podman, Apptainer, kubernetes et OpenStack.
Nous avons fournis une cinquantaine de conteneurs afin que tous les cours puissent se dérouler sans aucune installation des participants.
Un [cours spécifique de démonstration](https://cta-lapp.pages.in2p3.fr/COURS/GRAY_SCOTT_LECTURE_DEMO/) a été fourni pour clarifier les différents usages des conteneurs fournis.

Plusieurs containers sont disponibles pour chaque cours :
- **Light image** : pour les job scheduler (**HT Condor**, **Slurm**, etc)
- **Code server** : localement ou a distance avec **VSCode** intégré au navigateur (pas d'installation **VSCode** nécessaire)
- **Jupyter-hub** : si **Jupyter-hub** est disponible avec **Kubernetes**, **Docker Swarm** ou d'autres solutions. **Jupyter notebook** et **Code Server** sont fournis dans ces conteneurs

Tous les conteneurs ont été optimisés pour être le plus petit possible.

- Du 1 au 5 juillet :
	- Lundi 1 juillet, 9h-12h : Architecture CPU, Compilation
		- Pas d'image pour Architecture CPU
		- [Compiler optimisation](https://cta-lapp.pages.in2p3.fr/COURS/COMPILER_OPTIMISATION/index.html)
			- **Light image** 135 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/compiler_optimisation/compiler_optimisation_alpine_light:latest
			- **Code server** 317 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/compiler_optimisation/compiler_optimisation_alpine_micromamba_code_server:latest
			- **Jupyter-hub** 466 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/compiler_optimisation/compiler_optimisation_alpine_micromamba_vscode:latest
	- Lundi 1 juillet, 14h-18h : Profilage, Précision, Tests unitaires
		- Pas d'image pour le moment mais il n'y en aura certainement pas
	- Mardi 2 juillet, 9h-12h : C++ 17/20/23 sur CPU
		- [Introduction to C++ algorithms](https://cta-lapp.pages.in2p3.fr/COURS/INTRODUCTION_CPP_ALGORITHMS/) :
			- **Light image** 128 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_cpp_algorithms/introduction_cpp_algorithms_alpine_light:latest
			- **Code server** 310 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_cpp_algorithms/introduction_cpp_algorithms_alpine_micromamba_code_server:latest
			- **Jupyter-hub** 383 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_cpp_algorithms/introduction_cpp_algorithms_alpine_micromamba_vscode:latest
		- [Performance with Stencil](https://cta-lapp.pages.in2p3.fr/COURS/PERFORMANCE_WITH_STENCIL/) :
			- **Light image** 143 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/performance_with_stencil/performance_with_stencil_alpine_light:latest
			- **Code server** 325 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/performance_with_stencil/performance_with_stencil_alpine_micromamba_code_server:latest
			- **Jupyter-hub** OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/performance_with_stencil/performance_with_stencil_alpine_micromamba_vscode:latest
		- **Optional** lectures :
			- [Introduction to Maqao](https://cta-lapp.pages.in2p3.fr/COURS/INTRODUCTION_MAQAO/) :
				- **Light image** 135 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_maqao/introduction_maqao_alpine_light:latest
				- **Code server** 317 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_maqao/introduction_maqao_alpine_micromamba_code_server:latest
				- **Jupyter-hub** OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_maqao/introduction_maqao_alpine_micromamba_vscode:latest
			- [Introduction to Valgrind](https://cta-lapp.pages.in2p3.fr/COURS/INTRODUCTION_VALGRIND/) :
				- **Light image** 180 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_valgrind/introduction_valgrind_alpine_light:latest
				- **Code server** 362 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_valgrind/introduction_valgrind_alpine_micromamba_code_server:latest
				- **Jupyter-hub** OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_valgrind/introduction_valgrind_alpine_micromamba_vscode:latest
			- [Introduction to GDB](https://cta-lapp.pages.in2p3.fr/COURS/INTRODUCTION_GDB/) :
				- **Light image** 145 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_gdb/introduction_gdb_alpine_light:latest
				- **Code server** 326 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_gdb/introduction_gdb_alpine_micromamba_code_server:latest
				- **Jupyter-hub** OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_gdb/introduction_gdb_alpine_micromamba_vscode:latest
			- [Introduction to Code Optimisation](https://cta-lapp.pages.in2p3.fr/COURS/HPC_ASTRICS/) :
				- **Light image** 135 MB (python trouble) : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/hpc_astrics/introduction_to_code_optimisation_alpine_light:latest
				- **Code server** : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/hpc_astrics/introduction_to_code_optimisation_alpine_micromamba_code_server:latest
				- **Jupyter-hub** : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/hpc_astrics/introduction_to_code_optimisation_alpine_micromamba_vscode:latest
			- [Performance with NaN](https://cta-lapp.pages.in2p3.fr/COURS/PERFORMANCE_WITH_NAN/) :
				- **Light image** 148 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/performance_with_nan/performance_with_nan_alpine_light:latest
				- **Code server** 329 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/performance_with_nan/performance_with_nan_alpine_micromamba_code_server:latest
				- **Jupyter-hub** OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/performance_with_nan/performance_with_nan_alpine_micromamba_vscode:latest
			- [Development and code optimisation](https://cta-lapp.pages.in2p3.fr/COURS/DEVELOPMENT_AND_OPTIMISATION/) :
				- **Light image** 127 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/development_and_optimisation/development_and_optimisation_alpine_light:latest
				- **Code server** 309 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/development_and_optimisation/development_and_optimisation_alpine_micromamba_code_server:latest
				- **Jupyter-hub** OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/development_and_optimisation/development_and_optimisation_alpine_micromamba_vscode:latest
	- Mardi 2 juillet, 14h-18h : C++17 avec Sycl sur CPU
		- [Performance with stencil in Sycl](https://gitlab.in2p3.fr/CodeursIntensifs/grayscott/GrayScottSyclSetup/-/blob/main/README.md?ref_type=heads) :
			- **Light image** 2.43 GB OK : docker://gitlab-registry.in2p3.fr/codeursintensifs/grayscott/grayscottsyclsetup/gray_scott_sycl_ubuntu_light:latest
			- **Code server** 2.89 MB OK : docker://gitlab-registry.in2p3.fr/codeursintensifs/grayscott/grayscottsyclsetup/gray_scott_sycl_ubuntu_micromamba_code_server:latest
			- **Jupyter-hub** 2.99 GB : docker://gitlab-registry.in2p3.fr/codeursintensifs/grayscott/grayscottsyclsetup/gray_scott_sycl_ubuntu_micromamba_vscode:latest
	- Mercredi 3 juillet, 9h-12h : Fortran 2018 sur CPU
		- [Performance with stencil in Fortran](https://gitlab.in2p3.fr/lafage/GrayScottFortranTuto) :
			- **Light image** 141 MB OK : docker://gitlab-registry.in2p3.fr/lafage/grayscottfortrantuto/grayscott_fortran_tuto_alpine_light:latest
			- **Code server** 324 MB OK : docker://gitlab-registry.in2p3.fr/lafage/grayscottfortrantuto/grayscott_fortran_tuto_alpine_micromamba_code_server:latest
			- **Jupyter-hub** OK : docker://gitlab-registry.in2p3.fr/lafage/grayscottfortrantuto/grayscott_fortran_tuto_alpine_micromamba_vscode:latest
	- Mercredi 3 juillet, 14h-18h : Fortran 2018 sur CPU, Précision numérique avec Cadena, Profilage Mémoire
		- [Optimisation Racine cubique](https://cta-lapp.pages.in2p3.fr/COURS/OPTIMISATION_RACINE_CUBIQUE/) :
			- **Light image** 182 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/optimisation_racine_cubique/optimisation_cbrt_alpine_light:latest
			- **Code server** 343 MB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/optimisation_racine_cubique/optimisation_cbrt_alpine_micromamba_code_server:latest
			- **Jupyter-hub** OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/optimisation_racine_cubique/optimisation_cbrt_alpine_micromamba_vscode:latest
		- Pas d'images pour le cours Précision numérique avec Cadna
		- [Profilage mémoire](https://gitlab.inria.fr/svalat/gray-scott-lab) :
			- **Light image** 859 MB OK : docker://registry.gitlab.inria.fr/svalat/gray-scott-lab/mem-ubuntu:latest
			- **Code server** 1.05 GB OK : docker://registry.gitlab.inria.fr/svalat/gray-scott-lab/mem-ubuntu_micromamba_code_server:latest
			- **Jupyter-hub** 1.13 GB OK : docker://registry.gitlab.inria.fr/svalat/gray-scott-lab/mem-ubuntu_micromamba_vscode:latest
	- Jeudi 4 juillet : Rust sur CPU :
		- [Performance with stencil in Rust](https://gitlab.in2p3.fr/grasland/grayscott-with-rust) :
			- **Light image** 626 MB OK : docker://gitlab-registry.in2p3.fr/grasland/grayscott-with-rust/rust_light:latest
			- **Code server** 912 MB OK : docker://gitlab-registry.in2p3.fr/grasland/grayscott-with-rust/rust_code_server:latest
			- **Jupyter-hub** 1.011 MB : docker://gitlab-registry.in2p3.fr/grasland/grayscott-with-rust/rust_vscode:pipeline-latest
	- Vendredi 5 juillet : Python sur CPU
		- [Performance with stencil in Python](https://gitlab.in2p3.fr/alice.faure/gray-scott-python) :
			- **Jupyter** 1.11 GB (for laptop/server/Kubernetes) OK : docker://gitlab-registry.in2p3.fr/alice.faure/gray-scott-python/gray-scott-jupyter-micromamba:latest

- Du 8 au 12 juillet :
	- Lundi 8 juillet, 9h-12h : Architecture GPU, calcul massivement parallèle, NVC++
		- [Performance with stencil GPU](https://cta-lapp.pages.in2p3.fr/COURS/PERFORMANCE_WITH_STENCIL_GPU/index.html)
			- **"Light" image** 5.7 GB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/performance_with_stencil_gpu/performance_with_stencil_gpu_ubuntu_light:latest
			- **Code server** 5.91 GB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/performance_with_stencil_gpu/performance_with_stencil_gpu_ubuntu_micromamba_code_server:latest
			- **Jupyter-hub** 6.01 GB : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/performance_with_stencil_gpu/performance_with_stencil_gpu_ubuntu_micromamba_vscode:latest
		- [Introduction to HPCSDK](https://cta-lapp.pages.in2p3.fr/COURS/INTRODUCTION_HPCSDK/)
			- **"Light" image** 5.68 GB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_hpcsdk/introduction_to_hpcsdk_2403_ubuntu_light:latest
			- **Code server** 5.89 GB OK : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_hpcsdk/introduction_to_hpcsdk_2403_ubuntu_micromamba_code_server:latest
			- **Jupyter-hub** 5.99 GB : docker://gitlab-registry.in2p3.fr/cta-lapp/cours/introduction_hpcsdk/introduction_to_hpcsdk_2403_ubuntu_micromamba_vscode:latest
	- Lundi 8 juillet, 14h-18h : Calcul en C++ 20 avec Eve :
		- **Light Image** : docker://ghcr.io/jfalcou/compilers@sha256:f9254149cc723a1fe6011ae246c3c9009944087b931cb92e20d23acdc83650e3
	- Mardi 9 juillet, 9h-12h : Calculer avec Python sur GPU :
		- L'image est encore en travaux
	- Mardi 9 juillet, 14h-18h : Calculer avec Python sur GPU
		- L'image est encore en travaux
	- Mercredi 10 juillet, 9h-12h : Sycl C++17 sur GPU (même images que pour la partie CPU)
		- [Performance with stencil in Sycl](https://gitlab.in2p3.fr/CodeursIntensifs/grayscott/GrayScottSyclSetup/-/blob/main/README.md?ref_type=heads) :
			- **"Light" image** 5.07 GB OK : docker://gitlab-registry.in2p3.fr/codeursintensifs/grayscott/grayscottsyclsetup/gray_scott_sycl_ubuntu_cuda_light
			- **Code server** 5.29 GB OK : docker://gitlab-registry.in2p3.fr/codeursintensifs/grayscott/grayscottsyclsetup/gray_scott_sycl_ubuntu_cuda_micromama_code_server
			- **Jupyter-hub** 5.39 GB : docker://gitlab-registry.in2p3.fr/codeursintensifs/grayscott/grayscottsyclsetup/gray_scott_sycl_ubuntu_cuda_micromama_vscode
			- Mercredi 10 juillet, 14h-18h : Rust sur GPU avec Vulkan
	- Performance with stencil in Rust
		- [Performance with stencil in Rust](https://gitlab.in2p3.fr/grasland/grayscott-with-rust) :
			- **Light image** 626 MB OK : docker://gitlab-registry.in2p3.fr/grasland/grayscott-with-rust/rust_light:latest
			- **Code server** 912 MB OK : docker://gitlab-registry.in2p3.fr/grasland/grayscott-with-rust/rust_code_server:latest
			- **Jupyter-hub** 1.011 MB : docker://gitlab-registry.in2p3.fr/grasland/grayscott-with-rust/rust_vscode:pipeline-latest
	- Jeudi 11 juillet : 
		- [Performance with stencil in Fortran](https://gitlab.in2p3.fr/lafage/GrayScottFortranTuto)
			- **Light Image** 5.7 GB : docker://gitlab-registry.in2p3.fr/lafage/grayscottfortrantuto/grayscottfortrantuto_gpu_ubuntu_light:latest


## Les vidéos de l'école

Les vidéo de l'école ont été suivit en direct par près de 500 personnes par jour pendant les deux semaines de l'école et ces vidéos totalisent également 419 vue différée sur YouTube.

- [Jour 1 : CPU | Architecture, Vectorisation, Compilation et bien d’autres !](https://www.youtube.com/watch?v=ixbmAi5DW2g)
- [Jour 2 : CPU | Optimisation C++ sur CPU et Sycl](https://www.youtube.com/watch?v=m-h_hdKXl18)
- [Jour 3 : CPU | Fortran 2018, CADNA et Profilage Mémoire](https://www.youtube.com/watch?v=MBLteiqWk1U)
- [Jour 4 : CPU | Optimisation avec Rust sur CPU - Techniques et outils en action !](https://www.youtube.com/watch?v=hd8FI-YchDE)
- [Jour 5 : CPU | Calculer avec Python sur CPU avec Numba & JAX](https://www.youtube.com/watch?v=h32JkC69Z4o)
- [Jour 6 : GPU et C++ | Optimisation et Calcul Massivement Parallèle - NVC++ & Eve](https://www.youtube.com/watch?v=kicQvDkf5X4)
- [Jour 7 : GPU | Maîtrisez Python sur GPU avec CuPy, Cunumeric, JAX et PyTorch !](https://www.youtube.com/watch?v=QBR_t0bebLI)
- [Jour 8 : GPU | Sycl C++17 & Rust avec Vulkan en action !](https://www.youtube.com/watch?v=PIax5vCaioc)
- [Jour 9 : GPU | Fortran, Python, Particules galactiques et bien plus !](https://www.youtube.com/watch?v=gEbi5DP0EZA&t=18608s)


## Les sites satellites

Un Site Satellite retransmet en direct la formation de la Gray Scott School auprès de son propre public (employés, public externe, étudiants, etc).

- [https://www.l2it.in2p3.fr/](L2IT), [https://www.calmip.univ-toulouse.fr/](CALMIP), [https://cerfacs.fr/](CERFACS), [https://www.onera.fr/fr/centres/toulouse](ONERA) et CUTIS (Toulouse)
- [https://www.cppm.in2p3.fr/web/fr/index.html](CPPM (Marseille)
- [https://www.criann.fr/](CRIANN) (Rouen)
- [https://romeo.univ-reims.fr/](ROMEO) (Reims)
- [https://mdls.fr/](Maison de la Simulation) (IDF)
- [https://www.hpc-ai.mines-paristech.fr/](Mines Paris - PSL - Cemef) (Sophia Antipolis)
- [https://isdm.umontpellier.fr/](ISDM) (Montpellier)
- [https://www.utc.fr/](UTC : Université de technologie de Compiègne) (Compiègne)
- [https://www.enccb.be/GrayScott2024fr](Université de Namur) (Belgique)
- [https://um6p.ma/fr/um6p-college-computing](College of computing de l'UM6P) (Maroc)
- [https://cineri.sn/](CINERI : Cyber Infrastructure nationale pour l'Enseignement supérieur, la Recherche et l'innovation) (Sénégal)
- [https://www.glicid.fr/](GLICID) (Nantes)

Nous tenons à remercier le réseau [Mesonet]() et tous les sites satellites d'avoir participé à l'école.

[Vidéo de présentation des sites satellites](https://www.youtube.com/watch?v=G8GBDVdh2RE)


## Les Sponsors

L'école a été en partie sponsorisée par Code Reckons, Intel et Eviden.
En complément de la sponsorisation, Code Reckons à fourni un accès gratuit au 50 premières personnes inscrites à l'école et Eviden mis à disposition deux ingénieurs HPC qui ont pu participer à la journée bootstrap de l'école (à Annecy et à Toulouse).

## Statistiques de l'école

- 9 professeurs
- 3 modes de connexion
- 12 sites Satellites sur 4 pays (France, Belgique, Maroc, Sénégal)
- 18 webinaires techniques
- 642 inscris
- ~400 personnes tous les jours sur YouTube (sans doublon)
- ~200 personnes tous les jours sur Discord (sans doublon)
- 530 comptes Discord créés spécialement pour l'école
- 481 personnes qui ont participées à au moins 1 cours
- ~50 Containers-lectures compatible with Docker, Apptainer, Podman, Kubernetes et OpenStack

J'espère que ça montre pourquoi nous n'avons pas eu beaucoup d'autres activités Reprises ces derniers temps :).


