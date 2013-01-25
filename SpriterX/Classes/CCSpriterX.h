//------------------------------------------------------------------------
//	SCMLAnimator : KickStarter project Spriter renderer for cocos2d-x. 
//	Spriter website : http://www.kickstarter.com/projects/539087245/spriter
//------------------------------------------------------------------------
//	Licensed under the BSD license, see LICENSE in root for details.
//	Copyright (c) 2012 James Hui (a.k.a. Dr.Watson)
//	For latest updates, please visit http://jameshui.com
//------------------------------------------------------------------------
// I corrected a part of this code. (Jan.2013, j2doll)  
//------------------------------------------------------------------------

#ifndef _CC_SPRITER_X_H_
#define _CC_SPRITER_X_H_

#include <vector>
#include <string>
#include "cocos2d.h" // current cocos2d-x version is 2.x. (2.0.x ~ 2.1) 
#include "tinyxml/tinyxml.h" // TinyXML : http://www.sourceforge.net/projects/tinyxml

// Sprite: http://www.brashmonkey.com/ 
// NOTE: current Spriter version is 1.0. (alpha 2) 

class CCSpriterX;

namespace SCMLHelper
{
	struct File
	{
		File();
		~File();
		void Init(TiXmlNode *node);

		int id;
		std::string name;
		float width;
		float height;
		cocos2d::CCSprite *sprite;
	};

	class Folder
	{
	public:
		Folder();
		~Folder();
		void Init(TiXmlNode *node);
		int GetFileCount();
		File *GetFile(int index);
	protected:
		int mId;
		std::string mName;
		std::vector <File *> mFiles;
	};

	struct ObjectRef
	{
		void Init(TiXmlNode *node);

		int id;
		int timeline;
		int key;
		int z_index;
	};

	struct Object
	{
		void Init(TiXmlNode *node, CCSpriterX *animator);

		int folder;
		int file;
		float x;
		float y;
		float angle;
		float pivot_x;
		float pivot_y;
		int z_index;
		cocos2d::CCSprite *sprite;
	};

	class Key
	{
	public:
		Key();
		~Key();
		void Init(TiXmlNode *node, CCSpriterX *animator);
		int GetObjectRefCount();
		ObjectRef *GetObjectRef(int index);
		int GetObjectCount();
		Object *GetObject(int index);
		float GetTime();
		bool IsSpinCounterClockwise();
	protected: 
		int mId;
		float mTime;
		bool mSpinCounterClockwise;
		std::vector <Object *> mObjects;
		std::vector <ObjectRef *> mObjectRefs;
	};

	class Timeline
	{
	public:
		Timeline();
		~Timeline();
		void Init(TiXmlNode *node, CCSpriterX *animator);
		int GetKeyframeCount();
		Key *GetKeyframe(int index);
	protected:
		int mId;
		std::vector <Key *> mKeyframes;
	};

	class Animation
	{
	public:
		Animation();
		~Animation();
		void Update(float dt);
		void Init(TiXmlNode *node, CCSpriterX *animator);
		void Render();
		bool IsDone();
		void Restart();
		std::string GetName();
	protected:
		int mId;
		std::string mName;
		float mLength;
		bool mLooping;
		bool mDone;
		Timeline *mMainline;
		int mCurrKeyframe;
		std::vector <Timeline *> mTimelines;
		float mTimer;
		cocos2d::CCPoint mPosition;
	};


	class Entity
	{
	public:
		Entity();
		~Entity();
		void Update(float dt);
		void Render();
		void SetId(int id);
		void SetName(const char *name);
		std::string GetName(); 
		void AddAnimation(Animation *animation);
		void NextAnimation();
		bool SetCurrentAnimationIndex(unsigned int animationIndex);
		bool SetCurrentAnimationName(std::string animationName, int& animationIndex);
	private:
		int mId;
		std::string mName;
		std::vector <Animation *> mAnimations;
		int mCurrAnimation;
	};
}

/**
 * \class CCSpriterX 
 * \brief main sprite class for Spriter (only use this class)  
 */

#define MAX_SPRITERX_FOLDER  50 // decide the proper values. 
#define MAX_SPRITERX_ENTITY  50 

/**
 * \class CCSpriterX
 * \brief sprite class for Spriter of Brash Monkey 
*/
class CCSpriterX : public cocos2d::CCNode
{
protected:

	CCSpriterX(unsigned int maxFolderSize = MAX_SPRITERX_FOLDER, unsigned int maxEntitySize = MAX_SPRITERX_ENTITY);

public:	

	virtual ~CCSpriterX(); 

	static CCSpriterX* create(const char *filename, unsigned int maxFolderSize = MAX_SPRITERX_FOLDER, unsigned int maxEntitySize = MAX_SPRITERX_ENTITY);

	bool initWithFile(const char *filename);

	cocos2d::CCSprite* getSprite(unsigned int folderId, unsigned int fileId); 

	bool setCurrentAnimation(unsigned int animationId);  

	// see animation name of SCML. animation has a name and id. 
	bool setCurrentAnimation(std::string animationName);

	unsigned int getCurrentEntityIndex();

protected:

	virtual void draw(void);

	virtual void update(float dt);
	
protected: 

	std::vector <SCMLHelper::Folder *> mFolders;

	std::vector <SCMLHelper::Entity *> mEntities; 

	unsigned int mCurrEntity; // current entity index 

};



#endif
