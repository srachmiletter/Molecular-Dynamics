

# Molecular Dynamics Simulation of a Lennard-Jones Fluid

In order to gain an understanding of molecular dynamics simulations, a sample system was generated. The goal of molecular dynamics simulations is to solve Newton's equations of motion for a system of particles, and after equilibrating, measure some observable quantity. The system of choice was a multidimensional fluid with a Lennard-Jones (LJ) interaction potential. The LJ potential was chosen due to available benchmark values and ease of simplified units. These dimensionless units are defined by choosing $\sigma$, $m$, and $\epsilon$ to be the units of length, mass, and energy, respectively, and making the following replacements for length, energy, and time:

\begin{center}
$r \rightarrow r\sigma$

$E \rightarrow \epsilon E$

$t \rightarrow t\sqrt{\frac{m\sigma^2}{\epsilon}}$
\end{center}

In these units, the LJ potential is then defined as:

\begin{equation}
    V\left(r\right) = 4\epsilon\left[\left(\frac{\sigma}{r}\right)^{12} - \left(\frac{\sigma}{r}\right)^6\right]
\end{equation}

where $r$ is the distance between atoms. The $r^{-12}$ term describes Pauli repulsion while the $r^{-6}$ term is due to dipole-dipole attraction. A plot of this potential is shown below.

\begin{figure}[H]
    \centering
    \includegraphics[width=5in]{LJ}
    \caption{Lennard-Jones potential plotted in reduced units. $r_m$ is the distance at which the potential reaches its minimum \cite{7}.}
    \label{fig:LJ}
\end{figure}

Next, the velocity Verlet algorithm is introduced to integrate Newton's equations of motion \cite{1}. Starting with the two first-order differential equations of force, $x'\left(t\right) = v\left(t\right)$ and $v'\left(t\right) = a\left(t\right)$, the position function at time $t+dt$ can be Taylor expanded:

\begin{equation}
    x\left(t+dt\right) = x\left(t\right) + x'\left(t\right)dt + \frac{1}{2}x''\left(t\right)dt^2 + O\left(dt^3\right)
\end{equation}

Plugging in the original first-order differential equations: 

\begin{equation}
    x\left(t+dt\right) = x\left(t\right) + v\left(t\right)dt + \frac{1}{2}a\left(t\right)dt^2 + O\left(dt^3\right)
\end{equation}

Expanding the original velocity function gives:

\begin{equation}
    v\left(t+dt\right) = v\left(t\right) + v'\left(t\right)dt + \frac{1}{2}v''\left(t\right)dt^2 + O\left(dt^3\right)
\end{equation}

After expanding its derivative in the same fashion, plugging in and rearranging, the final equation becomes:

\begin{equation}
    v\left(t+dt\right) = v\left(t\right) + \frac{1}{2}\left(a\left(t+dt\right) + a\left(t\right)\right)dt + O\left(dt^3\right)
\end{equation}

With this, the velocity Verlet method can be executed in the following three steps: \smallskip

$1:$ Calculate $x\left(t+dt\right) = x\left(t\right) + v\left(t\right)dt + \frac{1}{2}a\left(t\right)dt^2$.

$2:$ Derive the force $a\left(t+dt\right)$ from the above LJ potential.

$3:$ Calculate $v\left(t+dt\right) = v\left(t\right) + \frac{1}{2}\left(a\left(t\right) + a\left(t+dt\right)\right)dt$



Once the position, velocity, and force of all particles can be calculated, so can the thermodynamic properties of interest. It is important to note that this velocity Verlet method is perfectly general, and any reasonable potential could be used to calculate the forces. As an example, the radial distribution function (RDF) as well as the velocity auto-correlation function of the system is shown below.



\begin{figure}[H]
    \centering
    \includegraphics[width=4.5in]{RDF}
    \caption{Radial distribution function and nearest neighbor count of a 216-particle Lennard-Jones system after equilibration.}
    \label{fig:RDF}
\end{figure}

\begin{figure}[H]
    \centering
    \includegraphics[width=4.5in]{vacf}
    \caption{Velocity auto-correlation function of a Lennard-Jones system.}
    \label{fig:vacf}
\end{figure}

In figure \ref{fig:RDF} above, the first peak of the RDF is indicative of the first coordination shell of the liquid and later shows no recurrent structure, as expected. It is important to note that after the first peak, the RDF fluctuates about 1 and then goes to zero due to the lack of a periodic boundary condition for the sake of an accurate nearest neighbor count. If the periodic boundary condition was preserved, it would fluctuate about 1 indefinitely. Similarly, the velocity auto-correlation function in figure \ref{fig:vacf} quickly goes to zero and fluctuates about that point, showing no correlation to its previous structure. Together, these show the system has no ``memory'' of its past self, and are indicative of accurate simulation.