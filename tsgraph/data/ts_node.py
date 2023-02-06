from .graph_wrapper import TSGraph


class Variable:
    """
    A representation for a node in a TSGraph. Actually only contains
    a graph reference and the assigned node ID; all operations on
    this class are directly propagated to the graph backend instead.
    """

    ref_id: int
    graph: TSGraph

    def __init__(self, graph: TSGraph, ref_id: int = -1):
        """
        The initialization of `Variable` has two cases:
            1. ref_id == -1: This instance should act as an input node,
            and upon initialization, call the C backend to allocate a
            new node, whose assigned node ID become the `ref_id` of
            this instance.
            2. ref_id != -1: This instance is just a link to an allocated
            node in the graph. Normally the user should not initialize
            a `Variable` with a `ref_id` manually, as the node ID is never
            explicitly exposed to the user.
        """

        self.graph = graph
        if ref_id > -1:
            self.ref_id = ref_id
        else:
            pass # TODO: allocate new node
