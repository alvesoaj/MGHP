# encoding: utf-8
require 'writeexcel'

def read_file(file_name)
	file = File.open(file_name, "r")
	data = file.read
	file.close
	return data
end

def treat_data(data)
	array_n1 = []
	
	data.split(/^----- Teste: [0-9]*$/).each do |n1|
		if n1 != ""
			array_n2 = []
			n1.split("\n\n").each do |n2|
				array_n2 << n2
			end
			array_n1 << array_n2
		end
	end

	array_n1.each do |n1|
		n1[0] = n1[0].gsub("\n", "").split(":"); n1[0][1] = n1[0][1].to_i;

		n1[1] = n1[1].split(",").map{|t| t.split(":")}; n1[1].map!{|t| [t[0].strip(), t[1].to_f]};

		n1[2] = n1[2].split(":"); n1[2][1] = n1[2][1].split(",").map!{|t| t.to_f};

		n1[3] = n1[3].split(":"); n1[3][1] = n1[3][1].gsub("\n", "").split("\t"); n1[3][1].map!{|t| t.split(",").map{|x| x.to_f}}; n1[3][1].delete_at(0);

		n1[4] = n1[4].gsub("\n", "").gsub("\t", "").split(":"); n1[4][1] = n1[4][1].split(",").map!{|t| t.to_f};

		n1[5] = n1[5].gsub("\n", "").gsub("\t", "").split(":"); n1[5][1] = n1[5][1].split(",").map!{|t| t.to_f};

		n1[6] = n1[6].gsub("\n", "").gsub("\t", "").split(":"); n1[6][1] = n1[6][1].split(",").map!{|t| t.to_f};

		n1[7] = n1[7].split(":"); n1[7][1] = n1[7][1].gsub("\n", "").split("\t"); n1[7][1].map!{|t| t.split(",").map{|x| x.to_f}}; n1[7][1].delete_at(0);
		
		n1[8] = n1[8].split(":"); n1[8][1] = n1[8][1].gsub("\n", "").split("\t"); n1[8][1].map!{|t| t.split(",").map{|x| x.to_f}}; n1[8][1].delete_at(0);

		n1[9] = n1[9].split(":"); n1[9][1] = n1[9][1].gsub("\n", "").split("\t"); n1[9][1].map!{|t| t.split(",").map{|x| x.to_f}}; n1[9][1].delete_at(0);

		n1[10] = n1[10].split(":"); n1[10][1] = n1[10][1].to_f;
	end

	return array_n1
end

def save_data()

	#folders = ["1936-1941", "1951-1956", "1971-1976", "1980-1985", "2000-2005"]
	folders = ["MLT"]
	
	#archives = ["teste-10_30abelhas-1000ciclos", "teste-10_30abelhas-2000ciclos", 
	#	"teste-10_30abelhas-5000ciclos", "teste-10_60abelhas-1000ciclos",
	#	"teste-10_60abelhas-2000ciclos", "teste-10_60abelhas-5000ciclos",
	#	"teste-10_120abelhas-1000ciclos", "teste-10_120abelhas-2000ciclos",
	#	"teste-10_120abelhas-5000ciclos", "teste-10_200abelhas-1000ciclos",
	#	"teste-10_200abelhas-2000ciclos", "teste-10_200abelhas-5000ciclos"]

	archives = ["teste-20_30abelhas-1000ciclos", "teste-20_30abelhas-2000ciclos", 
		"teste-20_30abelhas-5000ciclos", "teste-20_60abelhas-1000ciclos",
		"teste-20_60abelhas-2000ciclos", "teste-20_60abelhas-5000ciclos",
		"teste-20_120abelhas-1000ciclos", "teste-20_120abelhas-2000ciclos",
		"teste-20_120abelhas-5000ciclos", "teste-20_200abelhas-1000ciclos",
		"teste-20_200abelhas-2000ciclos", "teste-20_200abelhas-5000ciclos"]
	
	usinas = ["Emborcação", "Itumbiara"]

	folders.each do |folder|
		puts "Processando: "+folder
		# Create a new Excel Workbook
		workbook = WriteExcel.new("avaliacao-"+folder+".xls")

		archives.each do |archive|
			puts "\tAnalisando: "+archive

			path = "./"+folder+"/"+archive+".txt"

			data = treat_data(read_file(path))

			# Add worksheet(s)
			worksheet  = workbook.add_worksheet(archive)

			worksheet.set_column(0, 0, 30)
			worksheet.set_column(0, 1, 30)

			path = path.gsub(".txt", "").gsub(".", "").split(/(\/|-|_)/)
			
			tests = "Número de testes: "+path[8].to_s
			worksheet.write(0, 0, tests)
			period = "Amostras: "+path[2].to_s+"-"+path[4].to_s
			worksheet.write(0, 1, period)
			bees = "Número de abelhas: "+path[10].to_i.to_s
			worksheet.write(0, 2, bees)
			cicles = "Número de ciclos: "+path[12].to_i.to_s
			worksheet.write(0, 3, cicles)

			small = 999999999999
			small_id = -1

			data.each_with_index do |elem, index|
				ofset = index * 3

				worksheet.set_column(2, ofset, 30)

				worksheet.write(2, ofset, 'Teste '+(index+1).to_s)

				worksheet.write(3, ofset, elem[0])

				worksheet.write(4, ofset, elem[1][0])
				worksheet.write(5, ofset, elem[1][1])
				worksheet.write(6, ofset, elem[1][2])

				worksheet.write(7, ofset, elem[10])

				if elem[10][1] < small
					small = elem[10][1]
					small_id = index
				end
			end

			worksheet.write(9, 2, "O melhor teste foi o: "); worksheet.write(9, 3, small_id+1);
			worksheet.write(10, 2, "O menor custo foi: "); worksheet.write(10, 3, data[small_id][10][1])

			worksheet.write(12, 0, data[small_id][2][0]);
			data[small_id][2][1].each_with_index do |v, i|
				worksheet.write(13+i, 0, v)
			end

			worksheet.write(12, 2, data[small_id][3][0]);
			data[small_id][3][1].each_with_index do |element, u|
				worksheet.write(13, 2+u, usinas[u])
				element.each_with_index do |v, i|
					worksheet.write(14+i, 2+u, v)
				end
			end

			worksheet.write(12, 5, data[small_id][4][0]);
			data[small_id][4][1].each_with_index do |v, i|
				worksheet.write(13+i, 5, v)
			end

			worksheet.write(12, 7, data[small_id][5][0]);
			data[small_id][5][1].each_with_index do |v, i|
				worksheet.write(13+i, 7, v)
			end

			worksheet.write(12, 9, data[small_id][6][0]);
			data[small_id][6][1].each_with_index do |v, i|
				worksheet.write(13+i, 9, v)
			end

			worksheet.write(12, 11, data[small_id][7][0]);
			data[small_id][7][1].each_with_index do |element, u|
				worksheet.write(13, 11+u, usinas[u])
				element.each_with_index do |v, i|
					worksheet.write(14+i, 11+u, v)
				end
			end

			worksheet.write(12, 14, data[small_id][8][0]);
			data[small_id][8][1].each_with_index do |element, u|
				worksheet.write(13, 14+u, usinas[u])
				element.each_with_index do |v, i|
					worksheet.write(14+i, 14+u, v)
				end
			end

			worksheet.write(12, 17, data[small_id][9][0]);
			data[small_id][9][1].each_with_index do |element, u|
				worksheet.write(13, 17+u, usinas[u])
				element.each_with_index do |v, i|
					worksheet.write(14+i, 17+u, v)
				end
			end
		end

		# write to file
		workbook.close
	end
end

save_data()