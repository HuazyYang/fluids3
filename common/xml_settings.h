

#ifndef DEF_XML_SETTINGS
	#define DEF_XML_SETTINGS

	#include <string>
	#include <map>
	#include <memory>

	#include "app_util.h"

	#define XML_BADVAL		-65535

	namespace pugi {
		class xml_node;
		class xml_document;
	};

	class XmlSettings {
		public:
			XmlSettings();
			~XmlSettings ();
            bool Load(std::string filename);

			void assignValueF ( float* buf, std::string key );
			void assignValueD ( double* buf, std::string key );
			void assignValueV3 ( Vector3DF* buf, std::string key );
			void assignValueStr ( std::string& str, std::string key );
			
			bool setBase ( std::string xpath);

			//Utility
			static Vector3DF ParseVector3 ( std::string vec );
			static Vector4DF ParseVector4 ( std::string vec );

		private:
			std::unique_ptr<pugi::xml_document> mDocument;
			std::unique_ptr<pugi::xml_node> mRoot;
			std::unique_ptr<pugi::xml_node> mCurrBase;
	};

#endif