from tsgraph.backend import graph_new


class TSGraph:

    _graph: object

    def __init__(self):
        self._graph = graph_new()
