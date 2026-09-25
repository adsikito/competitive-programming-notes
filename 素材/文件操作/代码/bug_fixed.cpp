while (!stringeam.eof()) {
		
			stringeam >> s;
			
			if (stringeam.fail()) {
				break;
			}
			if (s == " ") {
				continue;
			}
			
			set_111.wordset_add(s);
			map_111.wordmap_add(s);
}