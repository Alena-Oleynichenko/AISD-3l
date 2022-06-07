#include<queue>
#include<vector>
#include<iostream>
using namespace std;
template<typename TVertex, typename TEdge>
class graph {
private:

	struct destination
	{
		TVertex dest;
		TEdge edge;
	};
	struct vertex
	{
		int id_v;
		TVertex data;
		std::vector<destination> dest;
		bool color;
	};
	std::vector<vertex> table;

public:
	int return_index(TVertex ver)
	{
		for (int i = 0; i < table.size(); i++)
		{
			if (table[i].data == ver) return table[i].id_v;
		}
		return -1;
	}
	TVertex Get(TVertex temp_)
	{
		return table[return_index(temp_)].data;
	}
	void add_v(TVertex _data)
	{
		if (return_index(_data) == -1)
		{
			vertex new_vertex;
			new_vertex.id_v = table.size();
			new_vertex.data = _data;
			table.push_back(new_vertex);
		}
		else throw "This vertex exists!";
	}
	void add_e(TVertex _s, TVertex _dest, TEdge _edge) // добавить ребро
	{
		int tmp_s_id = return_index(_s);
		int tmp_dest_id = return_index(_dest);
		if (tmp_s_id < 0) throw "Source does not exist";
		if (tmp_dest_id < 0) throw "Destination does not exist";
		destination New_Edge;
		New_Edge.dest = tmp_dest_id;
		New_Edge.edge = _edge;
		table[tmp_s_id].dest.push_back(New_Edge);
	}
	void delete_e(TVertex _s, TVertex _dest) // удаление ребра
	{
		int tmp_s_id = return_index(_s);
		int tmp_dest_id = return_index(_dest);
		if (tmp_s_id * tmp_dest_id < 0)  throw "Edge does not exist";
		for (size_t i = 0; i < table[tmp_s_id].dest.size(); i++)
		{
			if (table[tmp_s_id].dest[i].dest == tmp_dest_id)
			{
				for (int j = i; j < table[tmp_s_id].dest.size() - 1; j++)
				{
					table[tmp_s_id].dest[i] = table[tmp_s_id].dest[i + 1];

				}
				table[tmp_s_id].dest.pop_back();
			}
		}
	}
	void delete_v(TVertex _s) // удаление вершины
	{
		int index = return_index(_s);
		if (index < 0) throw "Vertex does not exist";
		for (int i = 0; i < index; i++)
		{
			for (size_t j = 0; j < table[i].dest.size(); j++)
			{
				if (table[i].dest[j].dest == index)
				{
					for (size_t k = j; k < table[i].dest.size() - 1; k++)
					{
						table[i].dest[k].dest = table[i].dest[k + 1].dest;
					}
					table[i].dest.pop_back();
				}
			}
		}
		for (size_t i = index + 1; i < table.size(); i++)
		{
			for (size_t j = 0; j < table[i].dest.size(); j++)
			{
				if (table[i].dest[j].dest == index)
				{
					for (size_t k = j; k < table[i].dest.size() - 1; k++)
					{
						table[i].dest[k].dest = table[i].dest[k + 1].dest;
					}
					table[i].dest.pop_back();
				}
			}
		}
		for (size_t i = index; i < table.size() - 1; i++)
		{
			table[i] = table[i + 1];
			table[i].id_v--;
		}
		table.pop_back();
	}
	void Print()
	{
		for (size_t i = 0; i < table.size(); i++)
		{
			std::cout << table[i].data << ": {";
			for (size_t j = 0; j < table[i].dest.size(); j++)
			{
				std::cout << table[i].dest[j].dest << "(" << table[i].dest[j].edge << ")";
			}
			std::cout << "}" << std::endl;
		}
	}
	void breadth(TVertex _s)
	{
		for (size_t i = 0; i < table.size(); i++)
		{
			table[i].color = false;
		}
		std::queue<vertex> temp;
		vertex tmp = table[return_index(_s)];
		temp.push(tmp);
		tmp.color = true;
		while (!temp.empty()) {
			vertex u = temp.front();
			temp.pop();
			for (auto elem : u.dest) {
				vertex& v = table[elem.dest];
				if (v.color == false) {
					v.color = true;
					temp.push(v);
				}
			}
			std::cout << u.data;
		}
	}
	void Belman(TVertex _s, TVertex _d)
	{
		if (return_index(_s) == -1 || return_index(_d) == -1) throw "Vertexs not exist";
		std::vector<double> d(table.size());
		for (size_t i = 0; i < table.size(); i++)
		{
			d[i] = INFINITY;
		}
		d[return_index(_s)] = 0;
		std::vector<std::vector<TVertex>> way(table.size());
		for (size_t i = 0; i < table.size(); i++)
		{
			for (size_t j = 0; j < table[i].dest.size(); j++)
			{
				if (d[i] + static_cast<double>(table[i].dest[j].edge) < d[table[i].dest[j].dest])
				{
					d[table[i].dest[j].dest] = d[i] + static_cast<double>(table[i].dest[j].edge);
					way[table[i].dest[j].dest] = way[i];
					way[table[i].dest[j].dest].push_back(table[i].id_v + 1);
				}
			}
		}
		if (d[return_index(_s)] != 0)
		{
			throw"ifinity cickle!!!";
		}
		for (size_t i = 0; i < table.size(); i++)
		{
			way[i].push_back(table[i].id_v + 1);
		}
		for (size_t j = 0; j < way[return_index(_d)].size(); j++)
		{
			std::cout << way[return_index(_d)][j] << "->";
		}
		std::cout << "end" << std::endl;

		if (d[return_index(_d)] == INFINITY)
		{
			std::cout << _s << "->" << _d << "=" << "No way";
		}
		else std::cout << _s << "->" << _d << "=" << d[return_index(_d)];

	}



};



int main()
{
	graph<int, int> first;
	first.add_v(1);
	first.add_v(2);
	first.add_v(3);
	first.add_v(4);
	first.add_v(5);
	first.add_e(1, 2, 1);
	first.add_e(2, 3, 1);
	first.add_e(1, 5, 4);
	first.add_e(4, 5, 4);
	first.add_e(3, 1, 6);
	first.add_e(4, 1, 1);
	first.delete_e(1, 5);
	first.Belman(1, 4);
	std::cout << "\n";
	first.breadth(1);
	graph<int, int> second;
	second.add_v(6);
	second.add_v(7);
	if (second.Get(6) != second.Get(7))
	{
		std::cout << "\n";
		std::cout << "Yes";
	}
	return 0;
}
