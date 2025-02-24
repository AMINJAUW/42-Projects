from qiskit.circuit import Gate
from qiskit import QuantumCircuit

# Create a custom gate class for our oracle
class FakeOracleGate(Gate):
    def __init__(self):
        """
        Initialize the oracle gate.
        It takes 4 qubits (3 inputs + 1 ancilla)
        """
        super().__init__('Uf', 4, [])
        
    def inverse(self):
        """
        The inverse of our oracle (required for Gate class)
        In this case, Uf is its own inverse
        """
        return FakeOracleGate()

def draw_fake_dj_circuit():
    """
    Compiles a Deutsch-Jozsa circuit with a custom Uf gate.
    """
    n = 3  # Number of input qubits
    qc = QuantumCircuit(n + 1, n)
    qc.x(n)  # Flip the last qubit to |1>
    qc.barrier()
    display(qc.draw('mpl'))
    qc.h(range(n + 1))  # Apply Hadamard gates

    # Add the custom Uf gate
    oracle = FakeOracleGate()
    qc.append(oracle, range(n + 1))

    qc.h(range(n))  # Apply final Hadamard gates
    qc.measure(range(n), range(n))  # Measure the first n qubits
    display(qc.draw('mpl'))
